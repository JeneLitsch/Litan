cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	cast.cxx
	compare.cxx
	convert.cxx
	json.cxx
	stringify.cxx
	to_value.cxx
	to_any.cxx
)