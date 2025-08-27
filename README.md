## MIPS-Interpreter
[![Architecture](https://img.shields.io/badge/Architecture-MIPS-blue?style=flat-square)](https://en.wikipedia.org/wiki/MIPS_architecture)
[![Language](https://img.shields.io/badge/Language-C++-orange?style=flat-square)](https://en.wikipedia.org/wiki/C%2B%2B)
[![GUI](https://img.shields.io/badge/GUI-Qt6-brightgreen?style=flat-square)](https://github.com/qt)
<br>
This project implements a MIPS interpreter written in C++. It provides an assembler, an execution engine and a [Qt6](https://github.com/qt) graphical debugger. It supports a wide range of instructions and system calls, based on a custom ISA.

### Features
- Assembler, interpreter, debugger.
- Support for R/I/J operations: arthimetic, logic, shifts, branches, jumps, loads, stores, multiplications, divisions (using hi, lo registers).
- Traps: `print_int`, `print_char`, `print_string`, `read_int`, `read_char`, `exit`.
- Machine state: 32 general purpose and special purpose registers `hi`, `lo`, `pc`.
- Two-pass assembly: support for labels, code (`.text`) and data (`.data`) sections, and common directives (`.word`, `.byte`, `.asciiz`).
- Test `.asm` files to verify functionality.

### Dependencies
- C++17 Compiler (GCC ≥ 10 or Clang ≥ 11)
- CMake ≥ 3.10
- Qt 6.2+ (only needed for the GUI debugger)

### Build
```bash
git clone https://github.com/alessiopiroli/mips-interpreter.git
cd mips-interpreter
mkdir build && cd build
cmake ..
make
```

### Run
```bash
# Assembly -> binary
./src/mips-assemble <input.asm> <output.bin>

# Execute binary
./src/mips-execute <input.bin>

# Run directly from assembly file
./src/mips-interpret <input.asm>

# Run and debug with the GUI
./src/mips-debugger/mips-debugger <input.asm>
```

### Debugger
On the left side of the window the assembly input file is shown. On the right side a view of the state of the PC register and the  general purpose registers is shown. A toggle can be pressed to view the values stored in decimal. At the bottom there is a bar where one of the following commands can be used:
- `reg <register_name>` to display the value of the register
- `mem<8/16/32> <address>` to display the value stored in a certain address.
<img width="1197" height="832" alt="image" src="https://github.com/user-attachments/assets/4cc199d4-e77b-49e1-8136-3cbd0cb2d540" />
