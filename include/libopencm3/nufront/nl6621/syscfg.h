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

#ifndef NUFRONT_NL6621_SYSCFG_H
#define NUFRONT_NL6621_SYSCFG_H

#include <libopencm3/nufront/memorymap.h>

#define SYSCFG_MODE         MMIO32(AHB_PMU_BASE + 0x1CU)
#define SYSCFG_CLK_CTRL     MMIO32(AHB_PMU_BASE + 0x20U)
#define SYSCFG_LSB_TIME     MMIO32(AHB_PMU_BASE + 0x24U)
#define SYSCFG_MSB_TIME     MMIO32(AHB_PMU_BASE + 0x28U)
#define SYSCFG_STRAPS       MMIO32(AHB_PMU_BASE + 0x2CU)
#define SYSCFG_SPI          MMIO32(AHB_PMU_BASE + 0x30U)
#define SYSCFG_MUX          MMIO32(AHB_PMU_BASE + 0x34U)
#define SYSCFG_WAKEUP_MSK   MMIO32(AHB_PMU_BASE + 0x38U)
#define SYSCFG_REDUN        MMIO32(AHB_PMU_BASE + 0x3CU)

/* use SPI instead of QSPI on QSPI pins */
#define SYSCFG_SPI_SPI         (1 << 0)

/**
 * enable GPIO mode on pins when corresponding bit is set.
 * n.b. GPIOs 0-2 are not implemented and activate alternate
 * functions below
 **/
#define SYSCFG_MUX_GPIO(gpio)  (gpio)
/* select alternate functions on pins */
#define SYSCFG_MUX_UART        (1 << 0)
#define SYSCFG_MUX_JTAG        (1 << 1)
#define SYSCFG_MUX_PAON        (1 << 2)

/**
 * Configuring bandwidth for... GPIOs?
 **/
#define SYSCFG_MODE_BW_20M      0x0
#define SYSCFG_MODE_BW_10M      0x1
#define SYSCFG_MODE_BW_5M       0x2
#define SYSCFG_MODE_BW_RSV      0x3
#define SYSCFG_MODE_BW_EN       (1 << 2)

/**
 * Configuring CPU clock 
 **/
#define SYSCFG_MODE_CLK_160M    (0x0 << 3)
#define SYSCFG_MODE_CLK_120M    (0x1 << 3)
#define SYSCFG_MODE_CLK_80M     (0x2 << 3)
#define SYSCFG_MODE_CLK_40M     (0x3 << 3)
#define SYSCFG_MODE_CLK_EN      (0x1 << 5)

/**
 * no idea. 
 **/
#define SYSCFG_MODE_SIMD_RST    (0x1 << 6)

/**
 * Peripheral clocks
 */
#define SYSCFG_CLK_APB_40M      (0x0)
#define SYSCFG_CLK_APB_20M      (0x1)
#define SYSCFG_CLK_APB_10M      (0x2)
#define SYSCFG_CLK_APB_RSVD     (0x3)
#define SYSCFG_CLK_WLAN_GATE_EN (0x1 << 2)
#define SYSCFG_CLK_APB1_GATE_EN (0x1 << 3)
#define SYSCFG_CLK_APB2_GATE_EN (0x1 << 4)

#endif /* NUFRONT_NL6621_SYSCFG_H */
