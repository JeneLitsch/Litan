cmake_minimum_required(VERSION 3.13)

add_library(libltnvm
	"VM.cxx"
	"Heap.cxx"
	"VMStack.cxx"
	"TypeTable.cxx"
	"gc.cxx"
)

target_link_libraries(libltnvm libltn)

add_subdirectory("native")
add_subdirectory("build_in")
add_subdirectory("external")
add_subdirectory("inst")
add_subdirectory("objects")
add_subdirectory("utils")