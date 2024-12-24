cmake_minimum_required(VERSION 3.13)

project(Litan)
set(CMAKE_CXX_STANDARD 20)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")

add_compile_options( 
	-O3 
	-W 
	-Wall 
	-Wextra 
	-pedantic 
	-Wpedantic 
	-pedantic-errors 
	-Wunused 
	-Wwrite-strings 
	-Wconversion 
	-Wunreachable-code 
	-Wuninitialized 
	-Wold-style-cast 
	-Walloca 
	-Wparentheses 
	-Wno-unknown-pragmas 
)
include_directories("./")
include_directories("./libs/stdxx")
add_subdirectory("ltn")
add_subdirectory("ltnc")
add_subdirectory("ltnvm")
add_subdirectory("cli")
add_subdirectory("test/test_plugin")
