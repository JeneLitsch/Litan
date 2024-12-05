cmake_minimum_required(VERSION 3.13)

project(Litan)
set(CMAKE_CXX_STANDARD 20)

add_executable(litan
	"litan.cxx"
	"shared/shared.cxx"
	"shared/file.cxx"
	"commands/build.cxx"
	"commands/exec.cxx"
	"commands/dump.cxx"
	"commands/run.cxx"
)

target_link_libraries(litan libltn libltnc libltnvm)
