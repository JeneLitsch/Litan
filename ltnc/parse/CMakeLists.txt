cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	BraceTracker.cxx
	parse_array.cxx
	parse_assign.cxx
	parse_binary.cxx
	parse_block.cxx
	parse_braces.cxx
	parse_condition.cxx
	parse_conditional.cxx
	parse_definition.cxx
	parse_enums.cxx
	parse_expression.cxx
	parse_function.cxx
	parse_if_else.cxx
	parse_loops.cxx
	parse_name.cxx
	parse_newvar.cxx
	parse_member_code.cxx
	parse_parenthesized.cxx
	parse_primary.cxx
	parse_reflect.cxx
	parse_statement.cxx
	parse_switch.cxx
	parse_type.cxx
	parse_unary.cxx
	parse.cxx
	tokenize.cxx
)
