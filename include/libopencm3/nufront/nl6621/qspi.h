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

#ifndef NUFRONT_NL6621_QSPI_H
#define NUFRONT_NL6621_QSPI_H

#include <stddef.h>
#include <libopencm3/nufront/memorymap.h>

#define QSPI_CTRL0              MMIO32(QSPI_BASE + 0x00)
#define QSPI_CTRL0_CONT		     (0x1 << 13)
#define QSPI_E2PR_STD            (0x0 << 10)
#define QSPI_E2PR_STD_FAST       (0x1 << 10)
#define QSPI_E2PR_DO_FAST        (0x2 << 10)
#define QSPI_E2PR_QO_FAST        (0x3 << 10)
#define QSPI_E2PR_DIO_FAST       (0x4 << 10)
#define QSPI_E2PR_QIO_FAST       (0x5 << 10)
#define QSPI_E2PR_QIO_WORD       (0x6 << 10)
#define QSPI_E2PR_MASK           (0x7 << 10)
#define QSPI_CTRL0_TMOD_RXTX     (0x0 << 8)
#define QSPI_CTRL0_TMOD_TX       (0x1 << 8)
#define QSPI_CTRL0_TMOD_RX       (0x2 << 8)
#define QSPI_CTRL0_TMOD_EER      (0x3 << 8)
#define QSPI_CTRL0_TMOD_MASK     (0x3 << 8)
#define QSPI_CTRL0_SCPOL_HI      (0x1 << 7)
#define QSPI_CTRL0_SCPH          (0x1 << 6)
#define QSPI_CTRL0_FRF_SPI       (0x0 << 4)
#define QSPI_CTRL0_FRF_SSP       (0x1 << 4)
#define QSPI_CTRL0_FRF_MW        (0x2 << 4)
#define QSPI_CTRL0_FRF_MASK      (0x3 << 4)
#define QSPI_CTRL0_DFS_SHFT       0
#define QSPI_CTRL0_DFS_MASK      (0xf << QSPI_CTRL0_DFS_SHFT)

#define QSPI_CTRL1              MMIO32(QSPI_BASE + 0x04)
#define QSPI_CTRL1_NDF_SHFT       0
#define QSPI_CTRL1_NDF_MASK      (0xffff << QSPI_CTRL1_NDF_SHFT)

#define QSPI_SSI                MMIO32(QSPI_BASE + 0x08)
#define QSPI_SSI_EN              (0x1 << 0)
#define QSPI_SSI_AHB_EN          (0x1 << 1)

#define QSPI_BAUD               MMIO32(QSPI_BASE + 0x0c)
#define QSPI_BAUD_MASK           (0xffff << 0)

#define QSPI_TXFTL              MMIO32(QSPI_BASE + 0x10)
#define QSPI_TXFTL_MASK          (0x1f << 0)

#define QSPI_RXFTL              MMIO32(QSPI_BASE + 0x14)
#define QSPI_RXFTL_MASK          (0xf << 0)

#define QSPI_TXFL               MMIO32(QSPI_BASE + 0x18)
#define QSPI_RXFL               MMIO32(QSPI_BASE + 0x1c)

#define QSPI_SR                 MMIO32(QSPI_BASE + 0x20)
#define QSPI_SR_RFF              (0x1 << 4)
#define QSPI_SR_RFNE             (0x1 << 3)
#define QSPI_SR_TFE              (0x1 << 2)
#define QSPI_SR_TFNF             (0x1 << 1)
#define QSPI_SR_BUSY             (0x1 << 0)

#define QSPI_IM                 MMIO32(QSPI_BASE + 0x24)
#define QSPI_INT_AHB             (0x1 << 5)
#define QSPI_INT_RXF             (0x1 << 4)
#define QSPI_INT_RXO             (0x1 << 3)
#define QSPI_INT_RXU             (0x1 << 2)
#define QSPI_INT_TXO             (0x1 << 1)
#define QSPI_INT_TXE             (0x1 << 0)

#define QSPI_IS                 MMIO32(QSPI_BASE + 0x28)
/* same bits as QSPI_IM */

#define QSPI_RIS                MMIO32(QSPI_BASE + 0x2c)
/* same bits as QSPI_IM */

#define QSPI_TXOIC              MMIO32(QSPI_BASE + 0x30)
#define QSPI_RXOIC              MMIO32(QSPI_BASE + 0x34)
#define QSPI_RXUIC              MMIO32(QSPI_BASE + 0x38)
#define QSPI_AHBICR             MMIO32(QSPI_BASE + 0x3c)
#define QSPI_IC                 MMIO32(QSPI_BASE + 0x40)

#define QSPI_HOLD_WP            MMIO32(QSPI_BASE + 0x44)
#define QSPI_HOLD_WP_HLD         (0x1 << 1)
#define QSPI_HOLD_WP_WP          (0x1 << 0)

#define QSPI_READ_CMD           MMIO32(QSPI_BASE + 0x48)
#define QSPI_READ_CMD_03         (0x00 << 0)
#define QSPI_READ_CMD_0B         (0x01 << 0)
#define QSPI_READ_CMD_3B         (0x02 << 0)
#define QSPI_READ_CMD_6B         (0x03 << 0)
#define QSPI_READ_CMD_BB         (0x04 << 0)
#define QSPI_READ_CMD_EB         (0x05 << 0)
#define QSPI_READ_CMD_E7         (0x06 << 0)
#define QSPI_READ_CMD_MASK       (0xff << 0)
#define QSPI_READ_CMD_FLSH_M     (0xff << 8)
#define QSPI_READ_CMD_STD        (0x0 << 16)
#define QSPI_READ_CMD_STD_FAST   (0x1 << 16)
#define QSPI_READ_CMD_DO_FAST    (0x2 << 16)
#define QSPI_READ_CMD_QO_FAST    (0x3 << 16)
#define QSPI_READ_CMD_DIO_FAST   (0x4 << 16)
#define QSPI_READ_CMD_QIO_FAST   (0x5 << 16)
#define QSPI_READ_CMD_QUI_WORD   (0x6 << 16)
#define QSPI_READ_CMD_MODE_MASK  (0x7 << 16)
#define QSPI_READ_CMD_RD_PREF    (0x1 << 19)


#define QSPI_PGM_CMD            MMIO32(QSPI_BASE + 0x4c)
#define QSPI_PGM_CMD_SHFT         0
#define QSPI_PGM_CMD_MASK        (0xff << 0)
#define QSPI_PGM_CMD_PSZE_256    (0x0 << 8)
#define QSPI_PGM_CMD_PSZE_512    (0x1 << 8)
#define QSPI_PGM_CMD_PSZE_1024   (0x2 << 8)
#define QSPI_PGM_CMD_PSZE_2048   (0x3 << 8)
#define QSPI_PGM_CMD_PSZE_MASK   (0x3 << 8)

#define QSPI_CACHE_FLUSH        MMIO32(QSPI_BASE + 0x50)

#define QSPI_CACHE_DIS_UPD      MMIO32(QSPI_BASE + 0x54)
#define QSPI_CACHE_DIS_UPD_EN    (0x1 << 0)

#define QSPI_TXF_FLUSH          MMIO32(QSPI_BASE + 0x58)
#define QSPI_RXF_FLUSH          MMIO32(QSPI_BASE + 0x5c)

#define QSPI_DMAC               MMIO32(QSPI_BASE + 0x60)
#define QSPI_DMAC_TDMA           (0x1 << 1)
#define QSPI_DMAC_RDMA           (0x1 << 0)

#define QSPI_DMATDL             MMIO32(QSPI_BASE + 0x64)
#define QSPI_DMATDL_MASK         (0x1f << 0)

#define QSPI_DMARDL             MMIO32(QSPI_BASE + 0x68)
#define QSPI_DMARDL_MASK         (0xf << 0)

#define QSPI_DR                 MMIO32(QSPI_BASE + 0x6c)
#define QSPI_DR_MASK             (0xffff << 0)

extern struct spi_master *qspi_init(uint32_t clk_div);

#endif /* NUFRONT_NL6621_QSPI_H */
