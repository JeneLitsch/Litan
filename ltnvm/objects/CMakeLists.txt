cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	"Clock.cxx"
	"NativeFunctionPointer.cxx"
	"FunctionPointer.cxx"
	"RandomEngine.cxx"
	"Type.cxx"
	"Object.cxx"
	"Coroutine.cxx"
)

add_subdirectory("iter")
add_subdirectory("container")
add_subdirectory("io")