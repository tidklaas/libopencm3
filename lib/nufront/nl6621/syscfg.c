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

int syscfg_clk_init(enum syscfg_cpuclk cpuclk,
                    enum syscfg_apbclk apbclk,
                    enum syscfg_gpiobw gpiobw)
{

    SYSCFG_MODE = gpiobw | SYSCFG_MODE_BW_EN
                | cpuclk | SYSCFG_MODE_CLK_EN
                | SYSCFG_MODE_SIMD_RST;

    SYSCFG_CLK_CTRL = apbclk
                    | SYSCFG_CLK_WLAN_GATE_EN
                    | SYSCFG_CLK_APB1_GATE_EN
                    | SYSCFG_CLK_APB2_GATE_EN;
    return 0;
}

long int syscfg_get_apbclk(void)
{
    long int apb_clk;

    apb_clk = 0;
    /* TODO: check for clock gating */
    switch(SYSCFG_CLK_CTRL & SYSCFG_CLK_APB_MASK){
    case SYSCFG_CLK_APB_40M:
        apb_clk = 40000000;
        break;
    case SYSCFG_CLK_APB_20M:
        apb_clk = 20000000;
        break;
    case SYSCFG_CLK_APB_10M:
        apb_clk = 10000000;
        break;
    default:
        /* TODO: enter debug mode? */
        apb_clk = -1;
    }

    return apb_clk;
}

long int syscfg_get_cpuclk(void)
{
    long int cpu_clk;

    cpu_clk = 0;
    if(SYSCFG_MODE & SYSCFG_MODE_CLK_EN){
        switch(SYSCFG_MODE & SYSCFG_MODE_CLK_MASK){
        case SYSCFG_MODE_CLK_160M:
            cpu_clk = 160000000;
            break;
        case SYSCFG_MODE_CLK_120M:
            cpu_clk = 120000000;
            break;
        case SYSCFG_MODE_CLK_80M:
            cpu_clk = 80000000;
            break;
        case SYSCFG_MODE_CLK_40M:
            cpu_clk = 40000000;
            break;
        default:
            /* TODO: enter debug mode? */
            cpu_clk = -1;
        }
    }

    return cpu_clk;
}
