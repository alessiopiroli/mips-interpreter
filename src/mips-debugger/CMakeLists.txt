find_package(Qt6 REQUIRED COMPONENTS Widgets)

if(Qt6_VERSION VERSION_GREATER_EQUAL "6.5.0")
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
endif()

qt_add_executable(mips-debugger
    mips-debugger.cpp
    debugger.hpp
    debugger.cpp
)

target_link_libraries(mips-debugger PRIVATE
    Qt6::Widgets
    mips-core
)

target_include_directories(mips-debugger PRIVATE ../mips-core)