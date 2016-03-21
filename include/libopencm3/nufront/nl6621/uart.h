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

#ifndef NUFRONT_NL6621_UART_H
#define NUFRONT_NL6621_UART_H

#include <libopencm3/nufront/memorymap.h>

#define UART_RBR         MMIO32(UART_BASE + 0x00U)
#define UART_THR         MMIO32(UART_BASE + 0x00U)
#define UART_DLL         MMIO32(UART_BASE + 0x00U)
#define UART_DLH         MMIO32(UART_BASE + 0x04U)
#define UART_IER         MMIO32(UART_BASE + 0x04U)
#define UART_IIR         MMIO32(UART_BASE + 0x08U)
#define UART_FCR         MMIO32(UART_BASE + 0x08U)
#define UART_LCR         MMIO32(UART_BASE + 0x0cU)
#define UART_MCR         MMIO32(UART_BASE + 0x10U)
#define UART_LSR         MMIO32(UART_BASE + 0x14U)
#define UART_MSR         MMIO32(UART_BASE + 0x18U)
#define UART_SCR         MMIO32(UART_BASE + 0x1cU)
#define UART_FAR         MMIO32(UART_BASE + 0x70U)
#define UART_USR         MMIO32(UART_BASE + 0x7cU)
#define UART_HTX         MMIO32(UART_BASE + 0xa4U)
#define UART_DMASA       MMIO32(UART_BASE + 0xa8U)

#define UART_IER_PTIME      (0x1 << 7)
#define UART_IER_EDSSI      (0x1 << 3)
#define UART_IER_ELSI       (0x1 << 2)
#define UART_IER_ETBEI      (0x1 << 1)
#define UART_IER_ERBFI      (0x1 << 0)

#define UART_IIR_FIFOSE     (0x3 << 6)
#define UART_IIR_MODSTAT    (0x0 << 0)
#define UART_IIR_NONE       (0x1 << 0)
#define UART_IIR_TX         (0x2 << 0)
#define UART_IIR_RX         (0x4 << 0)
#define UART_IIR_LINESTAT   (0x6 << 0)
#define UART_IIR_BUSY       (0x7 << 0)
#define UART_IIR_TIMEOUT    (0xc << 0)
#define UART_IIR_MASK       (0xf << 0)

#define UART_FCR_RT_SNGL    (0x0 << 6)
#define UART_FCR_RT_QURT    (0x1 << 6)
#define UART_FCR_RT_HALF    (0x2 << 6)
#define UART_FCR_RT_HIGH    (0x3 << 6)
#define UART_FCR_RT_MASK    (0x3 << 6)

#define UART_FCR_TE_EMPTY   (0x0 << 4)
#define UART_FCR_TE_LOW     (0x1 << 4)
#define UART_FCR_TE_QURT    (0x2 << 4)
#define UART_FCR_TE_HALF    (0x3 << 4)
#define UART_FCR_TE_MASK    (0x3 << 4)

#define UART_FCR_DMAM1      (0x1 << 3)

#define UART_FCR_XFIFOR     (0x1 << 2)
#define UART_FCR_RFIFOR     (0x1 << 1)
#define UART_FCR_FIFO_EN    (0x1 << 0)

#define UART_LCR_DLAB       (0x1 << 7)
#define UART_LCR_BRK        (0x1 << 6)
#define UART_LCR_STPA       (0x1 << 5)
#define UART_LCR_EPS        (0x1 << 4)
#define UART_LCR_PEN        (0x1 << 3)
#define UART_LCR_STOP       (0x1 << 2)
#define UART_LCR_DLS_5BIT   (0x0 << 0)
#define UART_LCR_DLS_6BIT   (0x1 << 0)
#define UART_LCR_DLS_7BIT   (0x2 << 0)
#define UART_LCR_DLS_8BIT   (0x3 << 0)
#define UART_LCR_DLS_MASK   (0x3 << 0)

#define UART_MCR_SIRE       (0x1 << 6)
#define UART_MCR_AFCE       (0x1 << 5)
#define UART_MCR_LB         (0x1 << 4)
#define UART_MCR_OUT2       (0x1 << 3)
#define UART_MCR_OUT1       (0x1 << 2)
#define UART_MCR_RTS        (0x1 << 1)
#define UART_MCR_DTR        (0x1 << 0)

#define UART_LSR_RFE        (0x1 << 7)
#define UART_LSR_TEMT       (0x1 << 6)
#define UART_LSR_THRE       (0x1 << 5)
#define UART_LSR_BI         (0x1 << 4)
#define UART_LSR_FE         (0x1 << 3)
#define UART_LSR_PE         (0x1 << 2)
#define UART_LSR_OE         (0x1 << 1)
#define UART_LSR_DR         (0x1 << 0)

#define UART_MSR_DCD        (0x1 << 7)
#define UART_MSR_RI         (0x1 << 6)
#define UART_MSR_DSR        (0x1 << 5)
#define UART_MSR_CTS        (0x1 << 4)
#define UART_MSR_DDCD       (0x1 << 3)
#define UART_MSR_TERI       (0x1 << 2)
#define UART_MSR_DDSR       (0x1 << 1)
#define UART_MSR_DCTS       (0x1 << 0)


#endif /* NUFRONT_NL6621_UART_H */
