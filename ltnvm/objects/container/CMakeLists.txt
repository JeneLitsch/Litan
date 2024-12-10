cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	"Array_get_member.cxx"
	"Array.cxx"
	"Tuple_get_member.cxx"
	"Tuple.cxx"
	"Map_get_members.cxx"
	"Map.cxx"
)