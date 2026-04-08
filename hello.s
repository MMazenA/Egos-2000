/*
 * (C) 2026, Cornell University
 * All rights reserved.
 *
 * Description: entry point of the bootloader
 *
 *
 * Stack pointer register - sp
 * li instruction loads instruction
 * li is considered an integer computation because it loads an integer in my stack pointer
 * call main is considered a control transfer instruction, we transfer control to hello.c::main
 *
 *
 */
    .section .text.enter
    .global _start





_start:
    li sp, 0x80400000
    call main 
_end:
    call _end
