cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	deduction.cxx
	encode.cxx
	to_string.cxx
	traits_castable.cxx
	traits_check.cxx
	Type.cxx
)
