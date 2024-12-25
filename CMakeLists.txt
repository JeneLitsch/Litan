cmake_minimum_required(VERSION 3.13)

project(Litan
	VERSION 0.0.1
	DESCRIPTION "A programming language"
	LANGUAGES CXX C
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")

set(WARNINGS
	"-W"
	"-Wall"
	"-Wextra"
	"-pedantic"
	"-Wpedantic"
	"-pedantic-errors"
	"-Wunused"
	"-Wwrite-strings"
	"-Wconversion"
	"-Wunreachable-code"
	"-Wuninitialized"
	"-Walloca"
	"-Wparentheses"
)

set(WARNINGS_CXX_ONLY
	"-Wold-style-cast"
)

set(WARNINGS_C_ONLY)

add_library(litan_config INTERFACE)
target_compile_options(litan_config INTERFACE "-O3" )
target_compile_options(litan_config INTERFACE ${WARNINGS})
target_include_directories(litan_config INTERFACE "./")
target_include_directories(litan_config INTERFACE "./libs/stdxx")

add_library(litan_config_cxx INTERFACE)
target_compile_features(litan_config_cxx INTERFACE "cxx_std_20")
target_link_libraries(litan_config_cxx INTERFACE litan_config)
target_compile_options(litan_config_cxx INTERFACE ${WARNINGS_CXX_ONLY})

add_library(litan_config_c INTERFACE)
target_compile_features(litan_config_c INTERFACE "c_std_99")
target_link_libraries(litan_config_c INTERFACE litan_config)
target_compile_options(litan_config_c INTERFACE ${WARNINGS_C_ONLY})

add_subdirectory("ltn")
add_subdirectory("ltnc")
add_subdirectory("ltnvm")
add_subdirectory("cli")
add_subdirectory("test/test_plugin")
