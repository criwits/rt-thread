set confirm off
set architecture riscv:rv32
target remote 127.0.0.1:26000
symbol-file rtthread.elf
set disassemble-next-line auto
set riscv use-compressed-breakpoints yes
