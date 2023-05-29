cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	cast.cxx
	compare.cxx
	convert.cxx
	stringify.cxx
	to_value.cxx
	to_variant.cxx
)