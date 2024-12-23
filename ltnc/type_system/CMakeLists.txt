cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	"operations.cxx"
)

add_subdirectory("types")