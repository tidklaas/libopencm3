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

#include <string.h>
#include <libopencm3/nufront/spi.h>
#include <libopencm3/nufront/flash.h>

#define TIMEOUT             1000
#define FRAME_SIZE          8
#define PAGE_SIZE           256
#define SECT_SIZE           4096
#define MAX_READ_LEN        7

#define CMD_SEQ_READ        0x03       /* sequential read       */
#define CMD_WREN            0x06       /* write enable          */
#define CMD_WRDIS           0x04       /* write disable         */
#define CMD_CHIP_ERASE      0xC7       /* chip erase            */
#define CMD_SECTOR_ERASE    0x20       /* sector erase  4K      */
#define CMD_BLOCK64_ERASE   0xD8       /* block erase, 64K      */
#define CMD_BLOCK32_ERASE   0x52       /* block erase, 32K      */
#define CMD_PAGE_WRITE      0x02       /* page program          */
#define CMD_RD_SR           0x05       /* read status register  */
#define CMD_WR_SR           0x01       /* write status register */
#define FLASH_SR_BUSY       (0x1 << 0) /* flash busy flag       */
#define FLASH_SR_WEL        (0x1 << 1) /* write enabled flag    */

#define CMD_ADDR_SIZE       4   /* 1 byte command, 3 bytes address */
#define prep_cmd_addr(cmd, addr)               \
        {                                      \
            tx_buf[0] = (cmd);                 \
            tx_buf[1] = ((addr) >> 16) & 0xff; \
            tx_buf[2] = ((addr) >> 8) & 0xff;  \
            tx_buf[3] = (addr) & 0xff;         \
        }

static struct spi_master *spi = NULL;
static struct spi_xfer xfer;
static uint8_t tx_buf[PAGE_SIZE + CMD_ADDR_SIZE];

size_t flash_get_pagesize(void)
{
    return (size_t) PAGE_SIZE;
}

size_t flash_get_erasesize(void)
{
    return (size_t) SECT_SIZE;
}

int flash_init(void)
{
    spi = qspi_init(0xc0);

    return spi == NULL ? -1 : 0;
}

static int read_sr(void)
{
    int result;

    tx_buf[0] = CMD_RD_SR;

    xfer.rx_buf = tx_buf;
    xfer.rx_len = 1;
    xfer.tx_buf = tx_buf;
    xfer.tx_len = 1;

    result = spi->wait(spi, TIMEOUT);
    if(result != 0){
        goto err_out;
    }

    result = spi->xfer(spi, &xfer);
    if(result != 0){
        goto err_out;
    }

    return (int) tx_buf[0];

err_out:
    result = -1;
    return result;
}

static int flash_wait_ready(void)
{
    int result;

    do{
        result = spi->wait(spi, TIMEOUT);
        if(result != 0){
            goto err_out;
        }

        result = read_sr();
        if(result < 0){
            goto err_out;
        }
    }while(result & FLASH_SR_BUSY);

    return 0;

err_out:
    return result;
}

static int write_enable(void)
{
    int result;

    result = flash_wait_ready();
    if(result != 0){
        goto err_out;
    }

    result = spi->wait(spi, TIMEOUT);
    if(result != 0){
        goto err_out;
    }

    tx_buf[0] = CMD_WREN;

    xfer.rx_buf = NULL;
    xfer.rx_len = 0;
    xfer.tx_buf = tx_buf;
    xfer.tx_len = 1;

    result = spi->xfer(spi, &xfer);

err_out:
    return result;
}



int flash_write(unsigned long addr, const uint8_t *buf, size_t len)
{
    int result;
    uint32_t page_addr, page_off;
    size_t chunk_len;

    if(spi == NULL){
        result = -1;
        goto err_out;
    }

    while(len > 0){
        page_off = addr % PAGE_SIZE;
        page_addr = addr - page_off;
        chunk_len = PAGE_SIZE - page_off;
        chunk_len = (len < chunk_len) ? len : chunk_len;

        result = write_enable();
        if(result != 0){
            goto err_out;
        }

        result = flash_wait_ready();
        if(result != 0){
            goto err_out;
        }

        prep_cmd_addr(CMD_PAGE_WRITE, page_addr);

        memset(&(tx_buf[CMD_ADDR_SIZE]), 0xFF, PAGE_SIZE);
        memcpy(&(tx_buf[CMD_ADDR_SIZE + page_off]), buf, chunk_len);

        xfer.rx_buf = NULL;
        xfer.rx_len = 0;
        xfer.tx_buf = tx_buf;
        xfer.tx_len = CMD_ADDR_SIZE + PAGE_SIZE;

        result = spi->xfer(spi, &xfer);
        if(result != 0){
            goto err_out;
        }

        len -= chunk_len;
        buf += chunk_len;
        addr += chunk_len;
    }

err_out:
    return result;
}

int flash_read(unsigned long addr, uint8_t *buf, size_t len)
{
    int result;

    if(spi == NULL){
        result = -1;
        goto err_out;
    }

    result = flash_wait_ready();
    if(result != 0){
        goto err_out;
    }

    prep_cmd_addr(CMD_SEQ_READ, addr);

    xfer.rx_buf = buf;
    xfer.rx_len = len;
    xfer.tx_buf = tx_buf;
    xfer.tx_len = CMD_ADDR_SIZE;

    result = spi->xfer(spi, &xfer);

err_out:
    return result;
}

int flash_erase(unsigned long addr, size_t len)
{
    int result;
    unsigned long start, end;

    if(spi == NULL){
        result = -1;
        goto err_out;
    }

    start = addr - (addr % SECT_SIZE);
    end = addr + len - 1;
    end -= (end % SECT_SIZE);

    while(start <= end){
        result = flash_wait_ready();
        if(result != 0){
            goto err_out;
        }

        result = write_enable();
        if(result != 0){
            goto err_out;
        }

        result = flash_wait_ready();
        if(result != 0){
            goto err_out;
        }

        prep_cmd_addr(CMD_SECTOR_ERASE, start);

        xfer.rx_buf = NULL;
        xfer.rx_len = 0;
        xfer.tx_buf = tx_buf;
        xfer.tx_len = CMD_ADDR_SIZE;

        result = spi->xfer(spi, &xfer);
        if(result != 0){
            goto err_out;
        }

        start += SECT_SIZE;
    }

err_out:
    return result;
}



