cmake_minimum_required(VERSION 3.13)

add_library(libltnvm
	LtnVM.cxx
	Heap.cxx
	Stack.cxx
	TypeTable.cxx
	gc.cxx
)

add_subdirectory(build_in)
add_subdirectory(external)
add_subdirectory(inst)
add_subdirectory(objects)
add_subdirectory(utils)