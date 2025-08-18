#include "../mips-core/machine_state.hpp"

int main() {
    MachineState machinestate(16 * 1024 * 1024);
    std::cout << "Initial register values" << std::endl;
    machinestate.print_registers();
}