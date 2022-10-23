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

int main(void)
{
    printf("Hello RISC-V!\n");
    for (int i = 0; i <= 100; i++) {
        printf("%d!\n", i);
    }
    // while (1) {
        printf("Sleeping...\n");
        // rt_thread_mdelay(1000);
        rt_thread_mdelay(10000);
    // }
    return 0;
}
