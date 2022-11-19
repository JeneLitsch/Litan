cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	Heap.cxx
	HeapGC.cxx
	Register.cxx
	Stack.cxx
)

add_subdirectory(objects)