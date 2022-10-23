/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "tick.h"
#include <riscv_io.h>
#include <encoding.h>

#define VIRT_CLINT_TIMEBASE_FREQ    (10000000)

static volatile uint64_t time_elapsed = 0;
static volatile unsigned long tick_cycles = 0;

static uint64_t get_ticks()
{
    __asm__ __volatile__(
        "rdtime %0"
        : "=r"(time_elapsed));
    return time_elapsed;
}

int tick_isr(void)
{
    int tick_cycles = VIRT_CLINT_TIMEBASE_FREQ / RT_TICK_PER_SECOND;
    rt_tick_increase();

    *(uint32_t*)CLINT_MTIMECMP(__raw_hartid()) = *(uint32_t*)CLINT_MTIME + tick_cycles;

    return 0;
}

/* Sets and enable the timer interrupt */
int rt_hw_tick_init(void)
{
    unsigned long interval = VIRT_CLINT_TIMEBASE_FREQ / RT_TICK_PER_SECOND;

    clear_csr(mie, MIP_MTIP);
    clear_csr(mip, MIP_MTIP);
    *(uint32_t*)CLINT_MTIMECMP(__raw_hartid()) = *(uint32_t*)CLINT_MTIME + interval;
    set_csr(mie, MIP_MTIP);

    return 0;
}
