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

#ifndef NUFRONT_FLASH_COMMON_H
#define NUFRONT_FLASH_COMMON_H

#include <stddef.h>

extern int flash_init(void);
extern int flash_read(unsigned long addr, uint8_t *buf, size_t len);
extern int flash_write(unsigned long addr, const uint8_t *buf, size_t len);
extern int flash_erase(unsigned long addr, size_t len);
extern size_t flash_get_pagesize(void);
extern size_t flash_get_erasesize(void);

#endif /* NUFRONT_FLASH_COMMON_H */
