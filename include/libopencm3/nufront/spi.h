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

#ifndef NUFRONT_SPI_COMMON_H
#define NUFRONT_SPI_COMMON_H


#if defined(NL6621)
    #include "nl6621/sspi.h"
    #include "nl6621/qspi.h"
#else
    #error "Nufront family not defined."
#endif

struct spi_xfer {
    const uint8_t *tx_buf;
    size_t tx_len;
    uint8_t *rx_buf;
    size_t rx_len;
};

struct spi_master {
	void *priv;
	int (*xfer)(struct spi_master *master, struct spi_xfer *xfer);
	int (*wait)(struct spi_master *master, uint32_t timeout);
};
#endif /* NUFRONT_SPI_COMMON_H */
