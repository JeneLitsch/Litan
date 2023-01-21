cmake_minimum_required(VERSION 3.0)

project(Litan)
set(CMAKE_CXX_STANDARD 20)

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
include_directories("./libs/api")
add_subdirectory(ltn)
add_subdirectory(ltnc)
add_subdirectory(ltnvm)
add_subdirectory(libs/api/test)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)

	add_executable(exeltn cli/ltn.cxx)
	target_link_libraries(exeltn libltn libltnc libltnvm)
	
	add_executable(exeltnc cli/ltnc.cxx)
	target_link_libraries(exeltnc libltn libltnc)

	add_executable(exeltnvm cli/ltnvm.cxx)
	target_link_libraries(exeltnvm libltn libltnvm)
	
	add_executable(exeltninfo cli/ltninfo.cxx)
	
else()
	add_library(litan Litan.cxx)
	target_link_libraries(litan libltn libltnc libltnvm)
endif()