add_library(mips-core
    mips-core/machine_state.cpp
    mips-core/machine_state.hpp
    mips-core/instruction.cpp
    mips-core/instruction.hpp
)

target_include_directories(mips-core PUBLIC mips-core)

add_executable(mips-interpret mips-interpret/main.cpp)

target_link_libraries(mips-interpret PRIVATE mips-core)