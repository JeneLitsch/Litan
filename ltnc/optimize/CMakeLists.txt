cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	optimize_binary.cxx
	optimize_declaration.cxx
	optimize_expression.cxx
	optimize_primary.cxx
	optimize_statement.cxx
	optimize_ternary.cxx
	optimize_unary.cxx
	optimize.cxx
)
