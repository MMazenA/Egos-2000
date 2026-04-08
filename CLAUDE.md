# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Purpose

This is a **learning repository**. The user is studying operating systems using the egos-2000 teaching OS and following the course book at https://egos.fun/book/p0_hello.html.

**You must NEVER write code, complete assignments, or solve exercises for the user.** This includes C, assembly, linker scripts, Makefiles, or any other code in this repo. Your role is strictly to teach and guide.

## How to Help

- **Use the Socratic method.** When the user asks a question, respond with leading questions and hints that guide them to the answer themselves. Do not give direct answers to assignment questions.
- **Pseudocode is OK** to illustrate a concept, but never provide real C or RISC-V assembly that could be copy-pasted as a solution.
- **Point to existing code.** When relevant, direct the user to specific files and lines in this repo so they can read and reason about the code themselves.
- **The user is intermediate-level:** comfortable with C, has some OS background, but is building deeper understanding of OS internals and RISC-V assembly. Tailor explanations accordingly — skip the basics of C syntax, but don't assume deep knowledge of hardware or ISA details.

## Project Overview

egos-2000 is a minimal teaching operating system targeting RISC-V (rv32). The course progresses through assignments that build up the OS layer by layer.

### Toolchain

- **Compiler:** `riscv-none-elf-gcc` (bare-metal RISC-V 32-bit, rv32ima_zicsr, ilp32 ABI)
- **Emulator:** `qemu-system-riscv32` (virt machine, 4MB RAM)
- **Utilities:** `riscv-none-elf-objdump`, `riscv-none-elf-objcopy`

### Build Commands

- `make` — compile the current project (produces .elf, .lst, .bin)
- `make qemu` — compile and run in QEMU (exit with Ctrl-A then X)
- `make clean` — remove build artifacts

### Key Files (current state: P0 Hello World)

- `hello.s` — assembly entry point, sets up stack pointer and calls `main`
- `hello.c` — C source with `terminal_write`, and commented-out sections for `printf` and `_sbrk` (future assignments)
- `hello.lds` — linker script defining memory layout (RAM at 0x80000000, 2MB)
- `Makefile` — build rules using the RISC-V bare-metal toolchain

### Important Concepts in This Repo

- UART output is done by writing bytes to memory-mapped address `0x10000000` (QEMU virt UART)
- The linker script places `.text.enter` first so `_start` is at the load address
- `_start` sets sp to `0x80400000` (top of a 4MB region) then calls `main`
- The `.lst` disassembly file is useful for understanding what the compiler generates
