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

#ifndef NUFRONT_NL6621_SSPI_H
#define NUFRONT_NL6621_SSPI_H

#include <stddef.h>
#include <libopencm3/nufront/memorymap.h>

#define SSPI_CTRL0               MMIO32(SSPI_BASE + 0x00)
#define SSPI_CTRL0_VFS_SHFT        12
#define SSPI_CTRL0_CFS_MASK       (0xf << SSPI_CTRL0_CFS_SHFT)
#define SSPI_CTRL0_SRL            (0x1 << 11)
#define SSPI_CTRL0_TMOD_RXTX      (0x0 << 8)
#define SSPI_CTRL0_TMOD_TX        (0x1 << 8)
#define SSPI_CTRL0_TMOD_RX        (0x2 << 8)
#define SSPI_CTRL0_TMOD_EER       (0x3 << 8)
#define SSPI_CTRL0_TMOD_MASK      (0x3 << 8)
#define SSPI_CTRL0_SCPOL_HI       (0x1 << 7)
#define SSPI_CTRL0_SCPH           (0x1 << 6)
#define SSPI_CTRL0_FRF_SPI        (0x0 << 4)
#define SSPI_CTRL0_FRF_SSP        (0x1 << 4)
#define SSPI_CTRL0_FRF_MW         (0x2 << 4)
#define SSPI_CTRL0_FRF_MASK       (0x3 << 4)
#define SSPI_CTRL0_DFS_SHFT        0
#define SSPI_CTRL0_DFS_MASK       (0xf << SSPI_CTRL0_DFS_SHFT)

#define SSPI_CTRL1               MMIO32(SSPI_BASE + 0x04)
#define SSPI_CTRL1_NDF_SHFT        0
#define SSPI_CTRL1_NDF_MASK       (0xffff << SSPI_CTRL1_NDF_SHFT)

#define SSPI_SSI                 MMIO32(SSPI_BASE + 0x08)
#define SSPI_SSI_EN               (0x1 << 0)

#define SSPI_MWC                 MMIO32(SSPI_BASE + 0x0c)
#define SSPI_MWC_MHS              (0x1 << 2)
#define SSPI_MWC_TXW              (0x1 << 1)
#define SSPI_MWC_SEQ              (0x1 << 0)

#define SSPI_SE                  MMIO32(SSPI_BASE + 0x10)
#define SSPI_SE_EN(x)             (0x1 << (x))

#define SSPI_BAUD                MMIO32(SSPI_BASE + 0x14)
#define SSPI_BAUD_MASK            (0xffff << 0)

#define SSPI_TXFTL               MMIO32(SSPI_BASE + 0x18)
#define SSPI_TXFTL_MASK           (0xffff << 0)

#define SSPI_RXFTL               MMIO32(SSPI_BASE + 0x1c)
#define SSPI_RXFTL_MASK           (0xffff << 0)

#define SSPI_TXFL                MMIO32(SSPI_BASE + 0x20)
#define SSPI_RXFL                MMIO32(SSPI_BASE + 0x24)

#define SSPI_SR                  MMIO32(SSPI_BASE + 0x28)
#define SSPI_SR_DCOL              (0x1 << 6)
#define SSPI_SR_TXE               (0x1 << 5)
#define SSPI_SR_RFF               (0x1 << 4)
#define SSPI_SR_RFNE              (0x1 << 3)
#define SSPI_SR_TFE               (0x1 << 2)
#define SSPI_SR_TFNF              (0x1 << 1)
#define SSPI_SR_BUSY              (0x1 << 0)

#define SSPI_IM                  MMIO32(SSPI_BASE + 0x2c)
#define SSPI_INT_MST              (0x1 << 5)
#define SSPI_INT_RXF              (0x1 << 4)
#define SSPI_INT_RXO              (0x1 << 3)
#define SSPI_INT_RXU              (0x1 << 2)
#define SSPI_INT_TXO              (0x1 << 1)
#define SSPI_INT_TXE              (0x1 << 0)

#define SSPI_IS                  MMIO32(SSPI_BASE + 0x30)
/* same bits as SSPI_IM */

#define SSPI_RIS                 MMIO32(SSPI_BASE + 0x34)
/* same bits as SSPI_IM */

#define SSPI_TXOIC               MMIO32(SSPI_BASE + 0x38)
#define SSPI_RXOIC               MMIO32(SSPI_BASE + 0x3c)
#define SSPI_RXUIC               MMIO32(SSPI_BASE + 0x40)
#define SSPI_MSTIC               MMIO32(SSPI_BASE + 0x44)
#define SSPI_IC                  MMIO32(SSPI_BASE + 0x48)

#define SSPI_DMAC                MMIO32(SSPI_BASE + 0x4c)
#define SSPI_DMAC_TDMA            (0x1 << 1)
#define SSPI_DMAC_RDMA            (0x1 << 0)

#define SSPI_DMATDL              MMIO32(SSPI_BASE + 0x50)
#define SSPI_DMATDL_MASK          (0xffff << 0)

#define SSPI_DMARDL              MMIO32(SSPI_BASE + 0x54)
#define SSPI_DMARDL_MASK          (0xffff << 0)

#define SSPI_ID                  MMIO32(SSPI_BASE + 0x58)
#define SSPI_SSI_VER             MMIO32(SSPI_BASE + 0x5c)

#define SSPI_DR                  MMIO32(SSPI_BASE + 0x60)
#define SSPI_DR_MASK              (0xffff << 0)

#define SSPI_RX_SPL_DL           MMIO32(SSPI_BASE + 0xf0)
#define SSPI_RX_SPL_DL_MASK       (0xff << 0)

#define SSPI_RSVD0               MMIO32(SSPI_BASE + 0xf4)
#define SSPI_RSVD1               MMIO32(SSPI_BASE + 0xf8)
#define SSPI_RSVD2               MMIO32(SSPI_BASE + 0xfc)

extern struct spi_master *sspi_init(uint32_t clk_div);

#endif /* NUFRONT_NL6621_SSPI_H */
