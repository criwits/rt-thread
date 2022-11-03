/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     bigmagic     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include <string.h>


int main(void) {
    rt_kprintf("RT-Thread on PGL22G RV32 IP Core!\n");
    rt_kprintf("Long Live CHIRO! In CHIRO We Trust!\n");
    int coremark_main(void);
    coremark_main();
    return 0;
}