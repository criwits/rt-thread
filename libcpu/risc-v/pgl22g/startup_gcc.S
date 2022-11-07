/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 * 2018/12/27     Jesven       Add SMP support
 * 2020/6/12      Xim          Port to QEMU and remove SMP support
 */

#define XSTATUS_FS         (3 << 13) /* initial state of FPU, clear to disable */
#define XSTATUS_PUM        (1 << 18)
#include <cpuport.h>

boot_hartid: .int
  .global      boot_hartid

  .global   _start
  .section ".start", "ax"
_start:
  // for sifive uart
  li a0,0x54000000
	// disable interrupts
	li a1,0
	sw a1,16(a0)
	// enable tx
	li a1,1
	sw a1,8(a0)
	// enable rx
	li a1,1
	sw a1,12(a0)

	// print START\n
	addi a1,zero,'S'
	addi a2,zero,'T'
	addi a3,zero,'A'
	addi a4,zero,'R'
	addi a5,zero,'T'
	addi a6,zero,'\n'
  sw a1,0(a0)
	sw a2,0(a0)
	sw a3,0(a0)
	sw a4,0(a0)
	sw a5,0(a0)
	sw a6,0(a0)

  # setup stacks per hart
  csrr t0, mhartid                  # read current hart id
  slli t0, t0, 10                   # shift left the hart id by 1024

  # park harts with id != 0
  csrr a0, mhartid                  # read current hart id
  bnez a0, park                     # if we're not on the hart 0

  csrw SRC_XIE, 0                   # clear Interrupt Registers
  csrw SRC_XIP, 0

  la t0, trap_entry
  csrw SRC_XTVEC, t0                # set Trap Vector Base Address Register

  /* set to disable FPU */
  li t0, XSTATUS_FS                 # close fpu
  csrc SRC_XSTATUS, t0

.option push
.option norelax
  la gp, __global_pointer$
.option pop

  la   sp, __stack_start__
  li   t0, __STACKSIZE__
  add  sp, sp, t0
  csrw SRC_XSCRATCH, sp
  j primary_cpu_entry

park:
    wfi
    j park
