cmake_minimum_required(VERSION 3.13)

add_library(libltnc
	CompilerError.cxx
	Ltnc.cxx
	Reporter.cxx
)

add_subdirectory(assemble)
add_subdirectory(ast)
add_subdirectory(compile)
add_subdirectory(inst)
add_subdirectory(lex)
add_subdirectory(optimize)
add_subdirectory(parse)
add_subdirectory(peephole)
add_subdirectory(print)
add_subdirectory(tokens)
add_subdirectory(type)
add_subdirectory(unfold)