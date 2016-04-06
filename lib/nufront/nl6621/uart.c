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

#include <stddef.h>
#include <stdbool.h>

#include <libopencm3/nufront/uart.h>
#include <libopencm3/nufront/gpio.h>
#include <libopencm3/nufront/syscfg.h>

int uart_init(uint32_t speed)
{
	uint32_t apb_clk, uart_div;
	int result;

	result = 0;
	apb_clk = syscfg_get_apbclk();
	if(apb_clk == 0){
	    result = -1;
	    goto err_out;
	}

	/* round clock divider to closest rate */
	uart_div = (apb_clk + (speed * 8)) / (speed * 16);

	/* disable GPIO function on UART pins */
	SYSCFG_MUX &= ~GPIO_UART_EN;

	/* wait until UART is no longer busy */
	while(UART_USR & UART_USR_BUSY)
        ;

	/* switch UART into configuration mode */
    while(!(UART_LCR & UART_LCR_DLAB)){
        UART_LCR = (UART_LCR_DLAB | UART_LCR_STOP | UART_LCR_DLS_8BIT);
    }

    /* set new clock divider */
    UART_DLH = (uart_div >> 8) & 0xff;
    UART_DLL = uart_div & 0xff;

    /* wait until UART is ready and leave configuration mode */
    while(UART_USR & UART_USR_BUSY)
        ;

    while(UART_LCR & UART_LCR_DLAB){
        UART_LCR = UART_LCR_DLS_8BIT;
    }

    /* reset and enable FIFOs */
    UART_FCR = (UART_FCR_XFIFOR | UART_FCR_RFIFOR | UART_FCR_FIFO_EN);

 err_out:
    return result;
}

void uart_putc(const char val)
{
    while((UART_LSR & UART_LSR_THRE) == 0)
        ;

    UART_THR = val;
}

void uart_puts(const char *str)
{
    bool cr_sent;

    cr_sent = false;
    while(*str != '\0'){
        if(*str == '\n' && cr_sent == false){
            uart_putc('\r');
            cr_sent = true;
            continue;
        }

        cr_sent = false;
        if(*str == '\r'){
            cr_sent = true;
        }

        uart_putc(*str++);
    }
}

char uart_getc(void)
{
    char val;

    while((UART_LSR & UART_LSR_DR) == 0)
        ;

    val = (char) (UART_RBR & 0xff);

    return val;
}
