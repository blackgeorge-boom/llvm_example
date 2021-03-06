cmake_minimum_required(VERSION 3.12)
project(llvm_example)

set(CMAKE_CXX_STANDARD 14)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(llvm_example main.cpp ast.h lexer.h lexer.cpp parser.h parser.cpp top_lvl_parser.cpp top_lvl_parser.h ast.cpp logger.cpp logger.h ir_opt.cpp ir_opt.h)
#add_executable(sample sample/sample.cpp)
#add_executable(sample_opt sample/sample_opt.cpp)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader mcjit native)

# Link against LLVM libraries
target_link_libraries(llvm_example ${llvm_libs})
#target_link_libraries(sample ${llvm_libs})
#target_link_libraries(sample_opt ${llvm_libs})
