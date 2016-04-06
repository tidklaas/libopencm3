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

#ifndef NUFRONT_NL6621_TIMER_H
#define NUFRONT_NL6621_TIMER_H

#include <libopencm3/nufront/memorymap.h>

#define TMR0    TMR0_BASE
#define TMR1    TMR1_BASE

/**
 * Register TMR_LOAD
 *
 * Initial value to be loaded into the timer register.
 * R/W 32 bit
 */
#define TMR_LOAD(tmr_base)      MMIO32((tmr_base) + 0x00)
#define TMR0_LOAD               TMR_LOAD(TMR0)
#define TMR1_LOAD               TMR_LOAD(TMR1)

/**
 * Register TMR_VAL
 *
 * Current timer value.
 * R/- 32 bit
 */
#define TMR_VAL(tmr_base)       MMIO32((tmr_base) + 0x04)
#define TMR0_VAL                TMR_VAL(TMR0)
#define TMR1_VAL                TMR_VAL(TMR1)

/**
 * Register TMR_CTRL
 *
 * Control timer operation.
 * R/W 4(?) bit
 *
 * [2] 0: interrupts not masked 
 *     1: interrupts not masked
 *
 * [1] 0: free running mode
 *     1: user-defined count mode
 * 
 * [0] 0: timer disabled
 *     1: timer enabled 
 */
#define TMR_CTRL(tmr_base)      MMIO32((tmr_base) + 0x08)
#define TMR0_CTRL               TMR_CTRL(TMR0)
#define TMR1_CTRL               TMR_CTRL(TMR1)
#define TMR_CTRL_MASK_IRQ       (0x1 << 2)
#define TMR_CTRL_MODE_USER      (0x1 << 1)
#define TMR_CTRL_EN             (0x1 << 0)

/**
 * Register TMR_EOI
 *
 * Clear pending interrupt. Reads always 0.
 * R/- 1 bit
 */
#define TMR_EOI(tmr_base)       MMIO32((tmr_base) + 0x0c)
#define TMR0_EOI                TMR_EOI(TMR0)
#define TMR1_EOI                TMR_EOI(TMR1)

/**
 * Register TMR_INTSTAT
 *
 * Shows interrupt status for timer.
 * R/- 1 bit
 */
#define TMR_INTSTAT(tmr_base)   MMIO32((tmr_base) + 0x10)
#define TMR0_INTSTAT            TMR_INTSTAT(TMR0)
#define TMR1_INTSTAT            TMR_INTSTAT(TMR1)

/**
 * Register TMRS_INTSTAT
 *
 * Contains the masked interrupt status for all timers.
 * R/- 2 bit
 */
#define TMRS_INTSTAT            MMIO32(TMR0_BASE + 0xa0)
#define TMRS_INTSTAT_TMR0       (0x1 << 0)
#define TMRS_INTSTAT_TMR1       (0x1 << 1)

/**
 * Register TMRS_EOI
 *
 * Reading this register will clear pending interrups for all timers
 * Always reads as zero.
 * R/- -
 */
#define TMRS_EOI                MMIO32(TMR0_BASE + 0xa4)

/**
 * Register TMRS_RAW_INTSTAT
 *
 * Contains the unmasked interrupt status for all timers.
 * Bit definitions are the same as TMRS_INTSTAT
 * R/- 2 bit
 */
#define TMRS_RAW_INTSTAT        MMIO32(TMR0_BASE + 0xa8)

/**
 * Register TMRS_COMP_VER
 *
 * Revision number of the timer component.
 * R/- 32 bit
 */
#define TMRS_COMP_VER           MMIO32(TMR0_BASE + 0xac)

#endif /* NUFRONT_NL6621_TIMER_H */
