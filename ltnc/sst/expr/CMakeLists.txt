cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	Binary.cxx
	Call.cxx
	Invoke.cxx
	InvokeMember.cxx
	Map.cxx
	Reflect.cxx
	Struct.cxx
	Ternary.cxx
	Unary.cxx
)
