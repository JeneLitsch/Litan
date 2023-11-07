cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	Array.cxx
	Binary.cxx
	Call.cxx
	Index.cxx
	Invoke.cxx
	InvokeMember.cxx
	Literal.cxx
	Map.cxx
	Reflect.cxx
	Struct.cxx
	Ternary.cxx
	Tuple.cxx
	Unary.cxx
)
