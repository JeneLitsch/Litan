cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE
	transpile_functional.cxx
	transpile_statement.cxx
	transpile_expression.cxx
	transpile.cxx
)

add_subdirectory(lang)