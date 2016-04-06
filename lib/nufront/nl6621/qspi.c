/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2016 Tido Klaassen <tido@4gh.eu>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/cm3/assert.h>
#include <libopencm3/nufront/spi.h>
#include <libopencm3/nufront/gpio.h>
#include <libopencm3/nufront/syscfg.h>

#define FRAME_SIZE  8
#define TIMEOUT     100

static int spi_xfer(struct spi_master *this, struct spi_xfer *xfer);
static int spi_wait(struct spi_master *this, uint32_t usecs);

static struct spi_master master_qspi = {
		.xfer = spi_xfer,
		.wait = spi_wait,
};

struct spi_master *qspi_init(uint32_t clk_div)
{
    //SYSCFG_SPI = 0;
    SYSCFG_SPI &= ~SYSCFG_SPI_QSPI;
    SYSCFG_MUX &= ~GPIO_QSPI_EN;

    /* disable controller */
    QSPI_SSI = 0;

    /* mask all interrupts */
    QSPI_IM = 0;

    /* disable DMA */
    QSPI_DMAC = 0;

    /* reset DMA threshold level */
    QSPI_DMATDL = 0;

    /* set clock divider */
    QSPI_BAUD = clk_div & QSPI_BAUD_MASK;

    /* configure controller */
    QSPI_CTRL0 = QSPI_CTRL0_TMOD_RXTX | QSPI_CTRL0_FRF_SPI
              | QSPI_CTRL0_SCPOL_HI  | QSPI_CTRL0_SCPH   | (FRAME_SIZE - 1);


    /* reset number of data frames configuration in CTRL1. 
     * Will not be used in RXTX mode anyways.              */

    QSPI_CTRL1 = 0;

    /* enable controller */
    QSPI_SSI = QSPI_SSI_EN;

    /* flush FIFOs, just in case */
    (void) QSPI_TXF_FLUSH;
    (void) QSPI_RXF_FLUSH;

    return &master_qspi;
}

static int spi_wait(struct spi_master *this __attribute__((unused)),
                    uint32_t usecs)
{
    int result;

    result = 0;
    while((QSPI_SR & QSPI_SR_BUSY) && usecs--)
        ;

    if(usecs == 0){
        result = -1;
    }

    return result;
}

#if defined(QSPI_RXTX_BROKEN)
/**
 * RXTX mode seems to be broken. Using a logic analyser I can see the TX buffer
 * and dummy bytes being sent out on MOSI and the response data comming in on
 * MISO, but nothing shows up in QSPI_DR.
 * We need a workaround for reading from flash, so we just intercept SEQ_READ
 * transfers and use the controller's Read-EEPROM function.
 */
#define MAX_FLASH_RD_SIZE   ((0x1 << 16) - 1)
#define min(a, b) ((a) <= (b) ? (a) : (b))
#define CMD_SEQ_READ        0x03
static void write_byte(uint8_t byte)
{
    while(!(QSPI_SR & QSPI_SR_TFNF))
        ;

    QSPI_DR = byte;
}

static uint8_t read_byte(void)
{
    while(!(QSPI_SR & QSPI_SR_RFNE))
        ;

    return (QSPI_DR & 0xff);
}

static int read_flash(struct spi_xfer *xfer)
{
    size_t chunk_len, rd_len;
    uint8_t cmd, *rx_buf;
    uint32_t addr;

    rd_len = 0;
    rx_buf = xfer->rx_buf;
    cmd = xfer->tx_buf[0];
    addr = (xfer->tx_buf[1] << 16)
         | (xfer->tx_buf[2] << 8)
         | xfer->tx_buf[3];

    while(rd_len < xfer->rx_len){
        chunk_len = min(xfer->rx_len - rd_len, MAX_FLASH_RD_SIZE);
        
        QSPI_SSI = 0;

        /* configure controller */
        QSPI_CTRL0 = QSPI_CTRL0_TMOD_EER | QSPI_CTRL0_FRF_SPI
                   | QSPI_CTRL0_SCPOL_HI  | QSPI_CTRL0_SCPH   | (FRAME_SIZE - 1);

        QSPI_CTRL1 = chunk_len - 1;

        QSPI_SSI = QSPI_SSI_EN;

        (void) QSPI_TXF_FLUSH;
        (void) QSPI_RXF_FLUSH;

        write_byte(cmd);
        write_byte((addr >> 16) & 0xff);
        write_byte((addr >>  8) & 0xff);
        write_byte(addr & 0xff);

        rd_len += chunk_len;
        addr += chunk_len;

        while(chunk_len > 0){
            *rx_buf++ = read_byte();
            --chunk_len;
        }
    }

    return 0;
}
#endif /* defined(QSPI_RXTX_BROKEN) */

static int spi_xfer(struct spi_master *this, struct spi_xfer *xfer)
{
    int result;
    uint8_t *rx_buf, data;
    const uint8_t *tx_buf;
    size_t rx_cnt, tx_cnt, xfer_len;

    /* sanity checks */
    cm3_assert(xfer->tx_len == 0 || xfer->tx_buf != NULL);
    cm3_assert(xfer->rx_len == 0 || xfer->rx_buf != NULL);

#if defined(QSPI_RXTX_BROKEN)
    /* workaround for broken rxtx mode */ 
    if(xfer->rx_len > 0 && xfer->tx_buf != NULL 
       && xfer->tx_buf[0] == CMD_SEQ_READ)
    {
        result = read_flash(xfer);
        goto err_out;
    }
#endif /* defined(QSPI_RXTX_BROKEN) */

    /**
     * reset controller
     */
    /* disable controller */
    QSPI_SSI = 0;

    /* configure controller */
    QSPI_CTRL0 = QSPI_CTRL0_TMOD_RXTX | QSPI_CTRL0_FRF_SPI
               | QSPI_CTRL0_SCPOL_HI  | QSPI_CTRL0_SCPH   | (FRAME_SIZE - 1);

    QSPI_SSI = QSPI_SSI_EN;

    (void) QSPI_TXF_FLUSH;
    (void) QSPI_RXF_FLUSH;

    result = spi_wait(this, TIMEOUT);
    if(result != 0){
        goto err_out;
    }

    rx_cnt = 0;
    tx_cnt = 0;
    rx_buf = xfer->rx_buf;
    tx_buf = xfer->tx_buf;
    xfer_len = xfer->tx_len + xfer->rx_len;
    while(rx_cnt < xfer_len){

        /* read bytes from RX FIFO when available*/
        if(QSPI_SR & QSPI_SR_RFNE){
            data = QSPI_DR;
            ++rx_cnt;

            /* discard the first tx_len dummy bytes */
            if(rx_cnt > xfer->tx_len){
                *rx_buf++ = data;
            }
        }

        /* send out bytes if TX FIFO is not full */
        if(tx_cnt < xfer_len && (QSPI_SR & QSPI_SR_TFNF))
        {
            /* send out data bytes from TX buffer first, then switch
             * to dummy value */
            if(tx_cnt < xfer->tx_len){
                QSPI_DR = *tx_buf++;
            } else {
                QSPI_DR = 42;
            }
            ++tx_cnt;
        }
    }

    while(QSPI_SR & QSPI_SR_BUSY)
        ;
    
    /* flush queues and wait for controller to settle */
    (void) QSPI_TXF_FLUSH;
    (void) QSPI_RXF_FLUSH;

    while(QSPI_SR & QSPI_SR_BUSY)
        ;

err_out:
    return result;
}


