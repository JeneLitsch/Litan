cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	inst_alloc.cxx
	inst_arithmetic.cxx
	inst_at_write.cxx
	inst_at.cxx
	inst_bitwise.cxx
	inst_build_in.cxx
	inst_capture.cxx
	inst_casts.cxx
	inst_compare.cxx
	inst_control_flow.cxx
	inst_debug.cxx
	inst_deref.cxx
	inst_invoke.cxx
	inst_iter.cxx
	inst_memory.cxx
	inst_newtype.cxx
	inst_static.cxx
	inst_struct.cxx
	inst_unary.cxx
	inst_unpack.cxx
	inst_values.cxx
	inst_yield.cxx
)