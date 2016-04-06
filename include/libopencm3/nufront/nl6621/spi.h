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

#ifndef NUFRONT_NL6621_SPI_H
#define NUFRONT_NL6621_SPI_H

#include <libopencm3/nufront/memorymap.h>

#define SPI_CTRL0               MMIO32(SPI_BASE + 0x00)
#define SPI_CTRL0_VFS_SHFT        12
#define SPI_CTRL0_CFS_MASK       (0xf << SPI_CTRL0_CFS_SHFT)
#define SPI_CTRL0_SRL            (0x1 << 11)
#define SPI_CTRL0_TMOD_RXTX      (0x0 << 8)
#define SPI_CTRL0_TMOD_TX        (0x1 << 8)
#define SPI_CTRL0_TMOD_RX        (0x2 << 8)
#define SPI_CTRL0_TMOD_EER       (0x3 << 8)
#define SPI_CTRL0_TMOD_MASK      (0x3 << 8)
#define SPI_CTRL0_SCPOL_HI       (0x1 << 7)
#define SPI_CTRL0_SCPH           (0x1 << 6)
#define SPI_CTRL0_FRF_SPI        (0x0 << 4)
#define SPI_CTRL0_FRF_SSP        (0x1 << 4)
#define SPI_CTRL0_FRF_MW         (0x2 << 4)
#define SPI_CTRL0_FRF_MASK       (0x3 << 4)
#define SPI_CTRL0_DFS_SHFT        0
#define SPI_CTRL0_DFS_MASK       (0xf << SPI_CTRL0_DFS_SHFT)

#define SPI_CTRL1               MMIO32(SPI_BASE + 0x04)
#define SPI_CTRL1_NDF_SHFT        0 
#define SPI_CTRL1_NDF_MASK       (0xffff << SPI_CTRL1_NDF_SHFT)

#define SPI_SSI                 MMIO32(SPI_BASE + 0x08)
#define SPI_SSI_EN               (0x1 << 0)

#define SPI_MWC                 MMIO32(SPI_BASE + 0x0c)
#define SPI_MWC_MHS              (0x1 << 2)
#define SPI_MWC_TXW              (0x1 << 1)
#define SPI_MWC_SEQ              (0x1 << 0)

#define SPI_SE                  MMIO32(SPI_BASE + 0x10)
#define SPI_SE_EN(x)             (0x1 << (x))

#define SPI_BAUD                MMIO32(SPI_BASE + 0x14)
#define SPI_BAUD_MASK            (0xffff << 0)

#define SPI_TXFTL               MMIO32(SPI_BASE + 0x18)
#define SPI_TXFTL_MASK           (0xffff << 0)

#define SPI_RXFTL               MMIO32(SPI_BASE + 0x1c)
#define SPI_RXFTL_MASK           (0xffff << 0)

#define SPI_TXFL                MMIO32(SPI_BASE + 0x20)
#define SPI_RXFL                MMIO32(SPI_BASE + 0x24)

#define SPI_SR                  MMIO32(SPI_BASE + 0x28)
#define SPI_SR_DCOL              (0x1 << 6)
#define SPI_SR_TXE               (0x1 << 5)
#define SPI_SR_RFF               (0x1 << 4)
#define SPI_SR_RFNE              (0x1 << 3)
#define SPI_SR_TFE               (0x1 << 2)
#define SPI_SR_TFNF              (0x1 << 1)
#define SPI_SR_BUSY              (0x1 << 0)

#define SPI_IM                  MMIO32(SPI_BASE + 0x2c)
#define SPI_INT_MST              (0x1 << 5)
#define SPI_INT_RXF              (0x1 << 4)
#define SPI_INT_RXO              (0x1 << 3)
#define SPI_INT_RXU              (0x1 << 2)
#define SPI_INT_TXO              (0x1 << 1)
#define SPI_INT_TXE              (0x1 << 0)

#define SPI_IS                  MMIO32(SPI_BASE + 0x30)
/* same bits as SPI_IM */

#define SPI_RIS                 MMIO32(SPI_BASE + 0x34)
/* same bits as SPI_IM */

#define SPI_TXOIC               MMIO32(SPI_BASE + 0x38)
#define SPI_RXOIC               MMIO32(SPI_BASE + 0x3c)
#define SPI_RXUIC               MMIO32(SPI_BASE + 0x40)
#define SPI_MSTIC               MMIO32(SPI_BASE + 0x44)
#define SPI_IC                  MMIO32(SPI_BASE + 0x48)

#define SPI_DMAC                MMIO32(SPI_BASE + 0x4c)
#define SPI_DMAC_TDMA            (0x1 << 1)
#define SPI_DMAC_RDMA            (0x1 << 0)

#define SPI_DMATDL              MMIO32(SPI_BASE + 0x50)
#define SPI_DMATDL_MASK          (0xffff << 0)

#define SPI_DMARDL              MMIO32(SPI_BASE + 0x54)
#define SPI_DMARDL_MASK          (0xffff << 0)

#define SPI_ID                  MMIO32(SPI_BASE + 0x58)
#define SPI_SSI_VER             MMIO32(SPI_BASE + 0x5c)

#define SPI_DR                  MMIO32(SPI_BASE + 0x60)
#define SPI_DR_MASK              (0xffff << 0)

#define SPI_RX_SPL_DL           MMIO32(SPI_BASE + 0xf0)
#define SPI_RX_SPL_DL_MASK       (0xff << 0)

#define SPI_RSVD0               MMIO32(SPI_BASE + 0xf4)
#define SPI_RSVD0               MMIO32(SPI_BASE + 0xf8)
#define SPI_RSVD0               MMIO32(SPI_BASE + 0xfc)

extern int spi_init(void);
extern ssize_t spi_read(uint8_t *buf, size_t len);
extern ssize_t spi_write(const uint8_t *buf, size_t len);
extern int spi_write_byte(uint8_t val);
extern int spi_wait_timeout(uint32_t usecs);

static inline void spi_wait(void)
{
    while(SPI_SR & SPI_SR_BUSY)
        ;
}

#endif /* NUFRONT_NL6621_SPI_H */
