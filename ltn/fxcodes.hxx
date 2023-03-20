#pragma once
#include <cstdint>
namespace ltn {
	enum class FxCode : std::uint8_t {
		SORT_ASCN = 0x00,
		SORT_DESC,
		IS_SORTED_ASCN,
		IS_SORTED_DESC,
		FIND,
		FILL,
		REVERSE,


		SPLIT = 0x10,
		RAND,
		RAND_INT,
		RAND_FLOAT,


		//functional
		ARITY = 0x20,

		//io
		IO_RESET_COLOR = 0x30,
		IO_SET_FG_COLOR,
		IO_SET_BG_COLOR,
		IO_CLOSE_STREAM,
		IO_IS_EOF,
		IO_PRINT,
		IO_READ_STR,
		IO_READ_LINE,
		IO_READ_BOOL,
		IO_READ_CHAR,
		IO_READ_INT,
		IO_READ_FLOAT,
		IO_READ_ALL,

		// string
		TO_STRING = 0x40,
		SPLIT_STRING,
		JOIN_STRING,

		// Math
		MIN = 0x50,
		MAX,
		CLAMP,
		ROUND,
		FLOOR,
		CEIL,
		ABS,
		SIN,
		COS,
		TAN,
		SQRT,
		HYPOT,
		LOG,
		LN,
		LD,
		LG,
		
	};
}