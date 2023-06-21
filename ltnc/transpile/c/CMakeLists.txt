cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	print.cxx
	# transpile_c_array.cxx
	# transpile_c_binary.cxx
	# transpile_c_block.cxx
	# transpile_c_call.cxx
	# transpile_c_conditional.cxx
	transpile_c_binding.cxx
	transpile_c_expression.cxx
	transpile_c_function.cxx
	# transpile_c_fx_ptr.cxx
	# transpile_c_global.cxx
	# transpile_c_if_else.cxx
	# transpile_c_iife.cxx
	# transpile_c_index.cxx
	# transpile_c_init.cxx
	# transpile_c_loops.cxx
	# transpile_c_primitives.cxx
	# transpile_c_read.cxx
	# transpile_c_reflect.cxx
	# transpile_c_return.cxx
	transpile_c_statement.cxx
	# transpile_c_switch.cxx
	# transpile_c_ternary.cxx
	# transpile_c_throw.cxx
	# transpile_c_type.cxx
	# transpile_c_unary.cxx
	# transpile_c_write.cxx
	transpile_c.cxx
)