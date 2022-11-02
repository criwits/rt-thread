/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>

extern unsigned int __stack_start__;
extern unsigned int __bss_start;
extern unsigned int __bss_end;

#define RT_HW_STACK_BEGIN   ((void *)&__stack_start__)
#define RT_HW_STACK_END     ((void *)(((rt_size_t)RT_HW_STACK_BEGIN) + __STACKSIZE__))
#define RT_HW_BSS_BEGIN     ((void *)&__bss_start)
#define RT_HW_BSS_END       ((void *)&__bss_end)
#define RT_HW_HEAP_BEGIN    ((void *)&__bss_end)
#define RT_HW_HEAP_END      ((void *)(((rt_size_t)RT_HW_HEAP_BEGIN) + HEAP_SIZE))

void rt_hw_board_init(void);
void rt_init_user_mem(struct rt_thread *thread, const char *name, unsigned long *entry);

#endif
