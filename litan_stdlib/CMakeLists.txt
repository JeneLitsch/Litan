cmake_minimum_required(VERSION 3.13)

set(LITAN_STDLIB_FILES
	"algorithm.ltn"
	"chrono.ltn"
	"container.ltn"
	"io.ltn"
	"json.ltn"
	"random.ltn"
	"type.ltn"
	"bits.ltn"
	"functional.ltn"
	"iter.ltn"
	"math.ltn"
	"string.ltn"
)

set(${LITAN_STDLIB_PATHS} "")

foreach(file ${LITAN_STDLIB_FILES})
    list(APPEND LITAN_STDLIB_PATHS ${CMAKE_SOURCE_DIR}/litan_stdlib/${file})
endforeach()

add_custom_command(
	OUTPUT litan_stdlib.c 
	COMMAND tool_embed_file litan_stdlib ${LITAN_STDLIB_PATHS}  
  	DEPENDS tool_embed_file ${LITAN_STDLIB_FILES}
)

add_library(litan_stdlib STATIC litan_stdlib.c)