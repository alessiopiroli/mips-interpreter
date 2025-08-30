# MIPS Project Report - Alessio Piroli

The main goal of this project was to develop an assembler and interpreter for the MIPS assembly language (32 bit) based on a custom instruction table.
The core was split in four major classes: `MachineState`, `Instruction`, `Assembler` and `Interpreter`. <br> 
The `Instruction` class is constructed with a raw `uint32_t` instruction and contains member functions that extract certain bit ranges (e.g., 31-26 would be the `opcode`, extracted with the `opcode` function). <br>
The `MachineState` class is responsible for the state of the `memory` and of the general purpose registers, as well as special purpose registers such as `hi`, `lo` and `pc`. In contains member functions which can set or get values from registers and also make writes and reads to memory. <br>
The `Assembler` class is responsible of 