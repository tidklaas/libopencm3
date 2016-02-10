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

#ifndef NUFRONT_NL6621_GPIO_H
#define NUFRONT_NL6621_GPIO_H

#include <libopencm3/include/nufront/memorymap.h>

#define GPIOA               GPIO_BASE

#define GPIO_DR(port)       MMIO32((port) + 0x00U)
#define GPIOA_DR            GPIO_DR(GPIOA)

#define GPIO_DDR(port)      MMIO32((port) + 0x04U)
#define GPIOA_DDR(port)     GPIO_DDR(GPIOA)

#define GPIO_INT_EN         MMIO32((port) + 0x30U)
#define GPIOA_INT_EN        GPIO_INT_EN(GPIOA)

#define GPIO_INT_MASK       MMIO32((port) + 0x34U)
#define GPIOA_INT_MASK      GPIO_INT_MASK(GPIOA)

#define GPIO_INT_TYPE       MMIO32((port) + 0x38U)
#define GPIOA_INT_TYPE      GPIO_INT_TYPE(GPIOA)

#define GPIO_INT_POL        MMIO32((port) + 0x3CU)
#define GPIOA_INT_POL       GPIO_INT_POL(GPIOA)

#define GPIO_INT_STAT       MMIO32((port) + 0x40U)
#define GPIOA_INT_STAT      GPIO_INT_STAT(GPIOA)

#define GPIO_INT_STAT_RAW   MMIO32((port) + 0x44U)
#define GPIOA_INT_STAT_RAW  GPIO_INT_STAT_RAW(GPIOA)

#define GPIO_INT_CLR        MMIO32((port) + 0x4CU)
#define GPIOA_INT_CLR       GPIO_INT_CLR(GPIOA)

#define GPIO_PORT_READ      MMIO32((port) + 0x50U)
#define GPIOA_PORT_READ     GPIO_PORT_READ(GPIOA)

#define GPIO_INT_SYNC       MMIO32((port) + 0x60U)
#define GPIOA_INT_SYNC      GPIO_INT_SYNC(GPIOA)

#define GPIO_ID_CODE        MMIO32((port) + 0x64U)
#define GPIOA_ID_CODE       GPIO_ID_CODE(GPIOA)

#define GPIO_VER_ID_CODE    MMIO32((port) + 0x6CU)
#define GPIOA_VER_ID_CODE   GPIO_VER_ID_CODE(GPIOA)

#define PMUX_REG_SPI        MMIO(AHB_PMU_BASE + 0x30U)
#define PMUX_REG_GPIO       MMIO(AHB_PMU_BASE + 0x34U)

#define PMUX_SPI_EN         (1 << 0)

#define PMUX_UART_EN        (1 << 0)
#define PMUX_JTAG_EN        (1 << 1)
#define PMUX_PAON_EN        (1 << 2)
#define PMUX_GPIO_EN(gpio)  (gpio)


#endif /* NUFRONT_NL6621_GPIO_H */
