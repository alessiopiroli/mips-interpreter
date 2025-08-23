add_library(mips-core
    mips-core/machine_state.cpp
    mips-core/machine_state.hpp
    mips-core/instruction.cpp
    mips-core/instruction.hpp
    mips-core/interpreter.cpp
    mips-core/interpreter.hpp
    mips-core/assembler.cpp
    mips-core/assembler.hpp
)

target_include_directories(mips-core PUBLIC mips-core)

add_executable(mips-interpret mips-interpret/interpret-main.cpp)
target_link_libraries(mips-interpret PRIVATE mips-core)

add_executable(mips-execute mips-execute/execute-main.cpp)
target_link_libraries(mips-execute PRIVATE mips-core)

add_executable(mips-assemble mips-assemble/assemble-main.cpp)
target_link_libraries(mips-assemble PRIVATE mips-core)