cmake_minimum_required(VERSION 3.13)

add_library(libltnvm
	cast.cxx
	compare.cxx
	convert.cxx
	LtnVM.cxx
	stringify.cxx
	to_value.cxx
	to_variant.cxx
)

target_link_libraries(libltnvm ${CMAKE_DL_LIBS})

add_subdirectory(build_in)
add_subdirectory(external)
add_subdirectory(inst)
add_subdirectory(memory)