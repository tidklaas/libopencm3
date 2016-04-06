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

#include <libopencm3/nufront/spi.h>
#include <libopencm3/nufront/gpio.h>
#include <libopencm3/nufront/syscfg.h>

#define FRAME_SIZE  8

static int spi_xfer(struct spi_master *master, struct spi_xfer *xfer);
static int spi_wait(struct spi_master *this, uint32_t usecs);

static struct spi_master master_sspi = {
		.xfer = spi_xfer,
        .wait = spi_wait,
};

struct spi_master *sspi_init(uint32_t clk_div)
{
    SYSCFG_SPI &= ~SYSCFG_SPI_QSPI;
    SYSCFG_MUX &= ~GPIO_QSPI_EN;

    /* disable controller */
    SSPI_SSI = 0;

    /* mask all interrupts */
    SSPI_IM = 0;

    /* disable DMA */
    SSPI_DMAC = 0;

    /* reset DMA threshold level */
    SSPI_DMATDL = 0;

    /* set clock divider */
    SSPI_BAUD = clk_div & SSPI_BAUD_MASK;

    /* configure controller */
    SSPI_CTRL0 = SSPI_CTRL0_TMOD_RXTX | SSPI_CTRL0_FRF_SPI
              | SSPI_CTRL0_SCPOL_HI  | SSPI_CTRL0_SCPH   | (FRAME_SIZE - 1);


    /* reset number of data frames configuration in CTRL1. 
     * Will not be used in RXTX mode anyways.
     */

    SSPI_CTRL1 = 0;

    /* enable chip select for chip 0 */
    SSPI_SE = SSPI_SE_EN(0);

    /* enable controller */
    SSPI_SSI = SSPI_SSI_EN;

    return &master_sspi;
}


static int spi_xfer(struct spi_master *master __attribute__((unused)), 
                    struct spi_xfer *xfer __attribute__((unused)))
{
    /* TODO */
    return -1;
}

static int spi_wait(struct spi_master *this __attribute__((unused)), 
                    uint32_t usecs)
{
    while((SSPI_SR & SSPI_SR_BUSY) && usecs--)
        ;

    return (int) !usecs;
}


