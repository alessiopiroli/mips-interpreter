# MIPS Project Report - Alessio Piroli

The main goal of this project was to develop an assembler and interpreter for the MIPS assembly language (32 bit) based on a custom instruction table.
The core functionalities are divided in to four classes: `MachineState`, `Instruction`, `Assembler` and `Interpreter`. <br>

The `Instruction` class constructor accepts a `uint32_t` variable representing an instruction and contains member functions that extract predefined bit ranges (e.g., `opcode()` extracts bit 31-26).
<br>

The `MachineState` class is the interface between the `Assembler`, `Interpreter` and the underlying structure. It implements the memory (an `std::vector<uint8_t>`), general purpose registers, special registers (i.e., `hi`, `lo` and `pc`) and member functions which allow for writing and reading values to and from them.
<br>

The `Assembler` class contains several `std::unordered_map<std::string, ...>` structures that map register name to identifiers, instructions mnemonics to their encoding and system calls to their corresponding codes.
The `pass1` function scans the assembly code to record addresses relative to labels and stores them in the `symbol_table`. It uses helper functions like `trim()` which remove leading and trailing white spaces.
The `pass2()` function is responsible of encode the instructions in to their machine-level representation.
This is achieved through helper functions like `encode_r_type()`, `encode_j_type()`, `encode_i_type()`, `encode_trap_type()`. They rely on data stored in `InstructionInfo` and the `symbol_table` to encode each operation in the correct binary format.
<br>

The `Interpreter` class defines two maps which are populated by its constructor: `r_type_funct_map` and `opcode_map`.  
The first associates function codes of `R-TYPE` instructions to `lambda`s that implement the execution semantics. 
Similarly, the second map links opcodes and `lambda`s for the remaining instructions.
The class implements a `step()` function which permits the execution of one operation stored in memory at a time. 
This member function proved particularly useful during the implementation of the debugger and the testing phrase.
A `run()` method is also implemented which simulates real execution.
<br>

A debugger with a graphical interface was also developed.
When launched with the command `mips-debugger <input.asm>`, an application window is opened and interaction is possible.
On the left side of the window the content of the assembly file is displayed.
On the right side the status of the `program counter` and general purpose registers is shown.
By toggling a checkbox users can display all values in decimal instead of hexadecimal.
At the bottom an input field is provided where users can type commands like `reg $name` and `mem8/mem16/mem32 address` to display register contents or values stored in memory addresses.
<br>

The core functionalities of the project were tested using the `GoogleTest` unit test framework.
The tests are divided in two sections, assembler tests and interpreter tests. 
In the assembler tests, one operation from each major type was tested. Similarly, the interpreter tests asserted the correct execution of operations.
<br>