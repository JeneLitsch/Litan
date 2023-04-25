cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	analyze_enum.cxx
	analyze_preset.cxx
	analyze_array.cxx
	analyze_binary.cxx
	analyze_bindings.cxx
	analyze_block.cxx
	analyze_call.cxx
	analyze_expression.cxx
	analyze_function.cxx
	analyze_fx_ptr.cxx
	analyze_static.cxx
	analyze_if_else.cxx
	analyze_iife.cxx
	analyze_index.cxx
	analyze_init.cxx
	analyze_lambda.cxx
	analyze_loops.cxx
	analyze_newvar.cxx
	analyze_params_args.cxx
	analyze_primitives.cxx
	analyze_read.cxx
	analyze_reflect.cxx
	analyze_return.cxx
	analyze_statement.cxx
	analyze_switch.cxx
	analyze_ternary.cxx
	analyze_throw.cxx
	analyze_typed_unary.cxx
	analyze_unary.cxx
	analyze_write.cxx
	analyze.cxx	
	conversion.cxx
	default_value.cxx
	error.cxx
	instantiate_type.cxx
)

add_subdirectory(utils)