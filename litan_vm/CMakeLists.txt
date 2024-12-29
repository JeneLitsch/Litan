cmake_minimum_required(VERSION 3.13)

add_library(litan_vm STATIC
	"VM.cxx"
	"Heap.cxx"
	"VMStack.cxx"
	"TypeTable.cxx"
	"gc.cxx"
)

target_link_libraries(litan_vm PUBLIC litan_config_cxx)
target_link_libraries(litan_vm PUBLIC litan_native_cxx)
target_link_libraries(litan_vm PUBLIC litan_core)

add_subdirectory("native")
add_subdirectory("external")
add_subdirectory("inst")
add_subdirectory("objects")
add_subdirectory("utils")
add_subdirectory("stdlib")