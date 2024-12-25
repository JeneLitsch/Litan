cmake_minimum_required(VERSION 3.13)

target_sources(litan_vm PRIVATE 
	"Clock.cxx"
	"NativeFunctionPointer.cxx"
	"FunctionPointer.cxx"
	"RandomEngine.cxx"
	"Type.cxx"
	"Object.cxx"
	"Coroutine.cxx"
	"Plugin.cxx"
)

add_subdirectory("iter")
add_subdirectory("container")
add_subdirectory("io")