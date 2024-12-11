cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	"Clock.cxx"
	"NativeFunctionPointer.cxx"
	"RandomEngine.cxx"
	"Type.cxx"
)

add_subdirectory("iter")
add_subdirectory("container")