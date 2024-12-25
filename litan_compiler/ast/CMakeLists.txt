cmake_minimum_required(VERSION 3.13)

add_subdirectory(bind)
add_subdirectory(decl)
add_subdirectory(expr)
add_subdirectory(stmt)


target_sources(litan_compiler PRIVATE 
	AST.cxx
)