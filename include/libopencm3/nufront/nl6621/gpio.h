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

#include <libopencm3/nufront/memorymap.h>

#define GPIOA               GPIO_BASE

/**
 * Register GPIOA_DR
 *
 * Values written to this register are output on the I/O signals for 
 * GPIO Port if the corresponding data direction bits are set to
 * Output mode and the corresponding control bit is set to Software 
 * mode. The value read back is equal to the last value written to 
 * this register.
 */

#define GPIO_DR(port)       MMIO32((port) + 0x00U)
#define GPIOA_DR            GPIO_DR(GPIOA)

/**
 * Register GPIOA_DDR
 *
 * Values written to this register independently control the direction
 * of the corresponding data bit.
 *
 * 0 – Input (default)
 * 1 – Output
 */
#define GPIO_DDR(port)      MMIO32((port) + 0x04U)
#define GPIOA_DDR(port)     GPIO_DDR(GPIOA)

/**
 * Register GPIOA_INT_EN
 *
 * Allows each bit of Port to be configured for interrupts. By default
 * the generation of interrupts is disabled. Whenever a 1 is  written 
 * to a bit of this register, it configures the corresponding bit on 
 * Port to become an interrupt;
 * otherwise, Port operates as a normal GPIO signal. Interrupts are
 * disabled on the corresponding bits of Port if the corresponding 
 * data direction register is set to Output or if mode is set to Hardware.
 *
 * 0 – Configure bit as normal GPIO signal (default)
 * 1 – Configure bit as interrupt
 */
#define GPIO_INT_EN         MMIO32((port) + 0x30U)
#define GPIOA_INT_EN        GPIO_INT_EN(GPIOA)

/**
 * Register GPIOA_INT_MASK
 *
 * Controls whether an interrupt on Port can create an interrupt for the 
 * interrupt controller by not masking it. By default, all interrupts bits
 * are unmasked. 
 * Whenever a 1 is written to a bit in this register, it masks the interrupt
 * generation capability for this signal; otherwise interrupts are all owed
 * through. The unmasked status can be read as well as the resultant status 
 * after masking.
 *
 * 0 – Interrupt bits are unmasked (default)
 * 1 – Mask interrupt
 */
#define GPIO_INT_MASK       MMIO32((port) + 0x34U)
#define GPIOA_INT_MASK      GPIO_INT_MASK(GPIOA)

/**
 * Register GPIOA_INT_TYPE
 *
 * Controls the type of interrupt that can occur on Port 
 * Whenever a 0 is written to a bit of this register, it configures the
 * interrupt type to be level-sensitive; otherwise, it is edge-sensitive.
 *
 * 0 – Level-sensitive (default)
 * 1 – Edge-sensitive
 */
#define GPIO_INT_TYPE       MMIO32((port) + 0x38U)
#define GPIOA_INT_TYPE      GPIO_INT_TYPE(GPIOA)

/**
 * Register GPIOA_INT_POL
 *
 * Controls the polarity of edge or level sensitivity that can occur on 
 * input of Port. Whenever a 0 is written to a bit of this register, it
 * configures the interrupt type to falling-edge or active-low sensitive;
 * otherwise, it is rising-edge or active-high sensitive.
 *
 * 0 – Active-low (default)
 * 1 – Active-high
 */
#define GPIO_INT_POL        MMIO32((port) + 0x3CU)
#define GPIOA_INT_POL       GPIO_INT_POL(GPIOA)

/**
 * Register GPIOA_INT_STAT
 *
 * Interrupt status of GPIO port
 */
#define GPIO_INT_STAT       MMIO32((port) + 0x40U)
#define GPIOA_INT_STAT      GPIO_INT_STAT(GPIOA)

/**
 * Register GPIO_INT_STAT_RAW
 *
 * Raw interrupt of status of GPIO port
 */
#define GPIO_INT_STAT_RAW   MMIO32((port) + 0x44U)
#define GPIOA_INT_STAT_RAW  GPIO_INT_STAT_RAW(GPIOA)

/**
 * Register GPIOA_INT_CLR
 *
 * Controls the clearing of edge type interrupts from Port. 
 * When a 1 is written into a corresponding bit of this register, the 
 * interrupt is cleared. 
 * All interrupts are cleared when Port is not configured for interrupts.
 *
 * 0 – No interrupt clear (default)
 * 1 – Clear interrupt
 */
#define GPIO_INT_CLR        MMIO32((port) + 0x4CU)
#define GPIOA_INT_CLR       GPIO_INT_CLR(GPIOA)

/**
 * Register GPIOA_PORT_READ
 *
 * When Port is configured as Input, then reading this location reads 
 * the values on the signal. 
 * When the data direction of Port is set as Output, reading this 
 * location reads the data register for Port.
 *
 * Reset Value: 0x0
 */
#define GPIO_PORT_READ      MMIO32((port) + 0x50U)
#define GPIOA_PORT_READ     GPIO_PORT_READ(GPIOA)

#define GPIO_INT_SYNC       MMIO32((port) + 0x60U)
#define GPIOA_INT_SYNC      GPIO_INT_SYNC(GPIOA)

#define GPIO_ID_CODE        MMIO32((port) + 0x64U)
#define GPIOA_ID_CODE       GPIO_ID_CODE(GPIOA)

/**
 * Register GPIOA_VER_ID_CODE
 *
 * ASCII value for each number in the version, followed by *. 
 * For example 32_30_31_2A represents the version 2.01*
 */
#define GPIO_VER_ID_CODE    MMIO32((port) + 0x6CU)
#define GPIOA_VER_ID_CODE   GPIO_VER_ID_CODE(GPIOA)

/**
 * Aliases for GPIO pin's alternative functions
 */
#define GPIO_SD_CMD           (0x1 << 3)
#define GPIO_SD_CLK           (0x1 << 4)
#define GPIO_SD_DATA0         (0x1 << 5)
#define GPIO_SD_DATA1         (0x1 << 6)
#define GPIO_SD_DATA2         (0x1 << 7)
#define GPIO_SD_DATA3         (0x1 << 8)
#define GPIO_I2C_SCL          (0x1 << 9)
#define GPIO_I2C_SDA          (0x1 << 10)
#define GPIO_UART_RX          (0x1 << 11)
#define GPIO_UART_TX          (0x1 << 12)
#define GPIO_CO_BT_ACT        (0x1 << 13)
#define GPIO_CO_BT_OVL        (0x1 << 14)
#define GPIO_CO_BT_PRI        (0x1 << 15)
#define GPIO_CO_WL_ACT        (0x1 << 16)
#define GPIO_I2S_SCLK         (0x1 << 17)
#define GPIO_I2S_SDAT         (0x1 << 18)
#define GPIO_I2S_LCLK         (0x1 << 19)
#define GPIO_I2S_MCLK         (0x1 << 20)
#define GPIO_QSPI_CLK         (0x1 << 21)
#define GPIO_QSPI_DO          (0x1 << 22)
#define GPIO_QSPI_DI          (0x1 << 23)
#define GPIO_QSPI_CS          (0x1 << 24)
#define GPIO_QSPI_WP          (0x1 << 25)
#define GPIO_QSPI_HLD         (0x1 << 26)
#define GPIO_SPI_CLK          (0x1 << 27)
#define GPIO_SPI_DI           (0x1 << 28)
#define GPIO_SPI_CS           (0x1 << 29)
#define GPIO_SPI_DO           (0x1 << 30)
#define GPIO_PWM0             (0x1 << 31)

/**
 * convenience alises for en/disabling all GPIOs for a given 
 * alternative function
 */
#define GPIO_SD_EN      (GPIO_SD_CMD   | GPIO_SD_CLK   | \
                         GPIO_SD_DATA0 | GPIO_SD_DATA1 | \
                         GPIO_SD_DATA2 | GPIO_SD_DATA3)

#define GPIO_I2C_EN     (GPIO_I2C_SCL | GPIO_I2C_SDA)

#define GPIO_UART_EN    (GPIO_UART_RX | GPIO_UART_TX)

#define GPIO_CO_EN      (GPIO_CO_BT_ACT | GPIO_CO_BT_OVL | \
                         GPIO_CO_BT_PRI | GPIO_CO_WL_ACT)

#define GPIO_I2S_EN     (GPIO_I2S_SCLK | GPIO_I2S_SDAT | \
                         GPIO_I2S_LCLK | GPIO_I2S_MCLK)

#define GPIO_QSPI_EN    (GPIO_QSPI_CLK | GPIO_QSPI_DO | \
                         GPIO_QSPI_DI  | GPIO_QSPI_CS | \
                         GPIO_QSPI_WP  | GPIO_QSPI_HLD)

#define GPIO_SPI_EN     (GPIO_SPI_CLK | GPIO_SPI_DI | \
                         GPIO_SPI_CS  | GPIO_SPI_DO)

#define GPIO_PWM0_EN    GPIO_PWM0

#endif /* NUFRONT_NL6621_GPIO_H */
