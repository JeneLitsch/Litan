cmake_minimum_required(VERSION 3.13)

project(Litan)
set(CMAKE_CXX_STANDARD 20)

add_executable(litan
	"litan.cxx"
	"shared/file.cxx"
	"shared/help.cxx"
	"shared/options.cxx"
	"commands/build.cxx"
	"commands/exec.cxx"
	"commands/dump.cxx"
	"commands/run.cxx"
)

target_link_libraries(litan PRIVATE
	litan_compiler
	litan_vm
)
