cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	compile_array.cxx
	compile_binary.cxx
	compile_block.cxx
	compile_call.cxx
	compile_conditional.cxx
	compile_expression.cxx
	compile_function.cxx
	compile_fx_ptr.cxx
	compile_global.cxx
	compile_if_else.cxx
	compile_iife.cxx
	compile_index.cxx
	compile_init.cxx
	compile_loops.cxx
	compile_primitives.cxx
	compile_read.cxx
	compile_reflect.cxx
	compile_return.cxx
	compile_statement.cxx
	compile_switch.cxx
	compile_ternary.cxx
	compile_throw.cxx
	compile_type.cxx
	compile_unary.cxx
	compile_write.cxx
	compile.cxx
)

add_subdirectory(build_in)