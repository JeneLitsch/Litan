cmake_minimum_required(VERSION 3.13)

add_library(libltnc
	CompilerError.cxx
	Label.cxx
	labels.cxx
	Ltnc.cxx
	make_jump_id.cxx
	Namespace.cxx
	Qualifiers.cxx
)

target_link_libraries(libltnc libltn)

add_subdirectory(analyze)
add_subdirectory(assemble)
add_subdirectory(ast)
add_subdirectory(compile)
add_subdirectory(inst)
add_subdirectory(optimize)
add_subdirectory(parse)
add_subdirectory(peephole)
add_subdirectory(print)
add_subdirectory(read_sources)
add_subdirectory(scoping)
add_subdirectory(source)
add_subdirectory(sst)
add_subdirectory(tokens)