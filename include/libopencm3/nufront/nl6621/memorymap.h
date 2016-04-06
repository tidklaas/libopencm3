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

#ifndef NUFRONT_NL6621_MEMORYMAP_H
#define NUFRONT_NL6621_MEMORYMAP_H

#include <libopencm3/cm3/memorymap.h>

/**
 * Base addresses for ROM, code RAM, SRAM0 and QSPI flash depend on
 * pin strapping 
 **/
#define ROM_SIZE        0x10000U
#define ROM_BASE_RM00   0x00000000U
#define ROM_BASE_RM01   0x00070000U
#define ROM_BASE_RM10   0x01000000U

#define CODE_SIZE       0x30000U
#define CODE_BASE_RM00  0x00010000U
#define CODE_BASE_RM01  0x00000000U
#define CODE_BASE_RM10  0x01010000U

#define SRAM0_SIZE      0x18000U
#define SRAM0_BASE_RM00 0x00080000U
#define SRAM0_BASE_RM01 0x00080000U
#define SRAM0_BASE_RM10 0x10080000U

#define FLASH_SIZE      0x1000000U
#define FLASH_BASE_RM00 0x18000000U
#define FLASH_BASE_RM01 0x18000000U
#define FLASH_BASE_RM10 0x00000000U

#if !defined(ADDR_REMAP)
#define ADDR_REMAP  0
#endif

#if ADDR_REMAP == 0
#define ROM_BASE    ROM_BASE_RM00
#define CODE_BASE   CODE_BASE_RM00
#define SRAM0_BASE  SRAM0_BASE_RM00
#define FLASH_BASE  FLASH_BASE_RM00
#elif ADDR_REMAP == 1
#define ROM_BASE    ROM_BASE_RM01
#define CODE_BASE   CODE_BASE_RM01
#define SRAM0_BASE  SRAM0_BASE_RM01
#define FLASH_BASE  FLASH_BASE_RM01
#elif ADDR_REMAP == 2
#define ROM_BASE    ROM_BASE_RM10
#define CODE_BASE   CODE_BASE_RM10
#define SRAM0_BASE  SRAM0_BASE_RM10
#define FLASH_BASE  FLASH_BASE_RM10
#else
#error "Invalid address remap mode"
#endif

/**
 * Ping pong buffers used to exchange data between main app and WiFi stack
 **/
#define SRAM1_SIZE  0x18000U
#define SRAM1_BASE  0x20000000U

#define SRAM2_SIZE  0x10000U
#define SRAM2_BASE  0x20040000U

/**
 * base addresses of peripheral blocks
 **/
#define PERIPH_BASE         0x40000000U

#define APB0_BASE           (PERIPH_BASE + 0x00000U)
#define APB1_BASE           (PERIPH_BASE + 0x40000U)
#define AHB_MAC0_BASE       (PERIPH_BASE + 0x80000U)
#define AHB_MAC1_BASE       (PERIPH_BASE + 0xA0000U)
#define AHB_SDIO_BASE       (PERIPH_BASE + 0xC0000U)
#define AHB_PMU_BASE        (PERIPH_BASE + 0x100000U)
#define QSPI_BASE           (PERIPH_BASE + 0x140000U)
#define GDMA_REG_BASE       (PERIPH_BASE + 0x180000U)

/**
 * peripherals in APB0 
 **/

#define SSPI_BASE           (APB0_BASE + 0x0000U)
#define TMR0_BASE           (APB0_BASE + 0x1000U)
#define TMR1_BASE           (APB0_BASE + 0x1014U)
#define PHY_BASE            (APB0_BASE + 0x2000U)
#define WDT0_BASE           (APB0_BASE + 0x4000U)
#define I2C_BASE            (APB0_BASE + 0x5000U)
#define IQ_CAL_BASE         (APB0_BASE + 0x6000U)
#define RF_SPI_BASE         (APB0_BASE + 0x7000U)
#define PWM_BASE            (APB0_BASE + 0x9000U)

/**
 * peripherals in APB1
 **/
#define GPIO_BASE           (APB1_BASE + 0x0000U)
#define UART_BASE           (APB1_BASE + 0x1000U)
#define EFUSE_BASE          (APB1_BASE + 0x2000U) 
#define I2S_BASE            (APB1_BASE + 0x3000U)

#endif /* NUFRONT_NL6621_MEMORYMAP_H */
