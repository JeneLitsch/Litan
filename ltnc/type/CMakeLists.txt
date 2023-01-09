cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	check.cxx
	deduction.cxx
	encode.cxx
	to_string.cxx
	Type.cxx
)
