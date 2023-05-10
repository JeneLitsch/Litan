cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	Clock.cxx
	Iterator.cxx
	RandomEngine.cxx
	Type.cxx
)

add_subdirectory(iter)