cmake_minimum_required(VERSION 3.13)

add_library(test_plugin SHARED
	"test_plugin.c"

	"is_type.c"
	"as_type.c"
)