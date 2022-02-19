#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		// System
		EXIT = 0x00,
		ERROR,
		STATE,
		TRY,
		THROW,
		
		// Binary arithmetic
		ADD = 0x10,
		SUB,
		MLT,
		DIV,
		MOD,

		// Comparisons
		EQL = 0x18,
		UEQL,
		SML,
		BGR,
		SMLEQL,
		BGREQL,
		
		// Shift
		SHIFT_L,
		SHIFT_R,

		// Unary operators
		NEG = 0x20,
		NOT,
		INC,
		DEC,
		
		// Primitives
		NEWI = 0x30,
		NEWF,
		NEWU,
		NEWC,
		TRUE,
		FALSE,
		NVLL,

		// Controlflow and functions
		JUMP = 0x40,
		CALL,
		RETURN,
		IF,
		INVOKE,
		EXTERNAL,
		ALGORITHM,
		CAPTURE,
		PARAMETERS,

		// Allocations
		NEWARR = 0x50,
		NEWSTR,
		NEWOUT,
		NEWIN,
		NEWFX,
		NEWCLOCK,
		NEWSTRUCT,
		NEWRANGE,
		NEWSTACK,
		NEWQUEUE,
		NEWMAP,

		// Stack reading
		READ = 0x60,
		WRITE,
		SCRAP,
		MAKEVAR,
		READ_X,
		WRITE_X,
		SWAP,

		// Fast stack reading
		READ_0 = 0x68,
		READ_1,
		READ_2,
		READ_3, 
		WRITE_0,
		WRITE_1,
		WRITE_2,
		WRITE_3,

		// IO
		OUT = 0x70,
		IN_STR,
		IN_LINE,
		IN_INT,
		IN_FLOAT,
		IS_EOF,

		// Math
		MIN = 0x80,
		MAX,
		ROUND,
		FLOOR,
		CEIL,
		ABS,
		HYPOT,
		SQRT,
		LOG,
		LN,
		POW,
		SIN,
		COS,
		TAN, 

		// Collections and containers
		SIZE = 0xa0,
		AT,
		AT_WRITE,
		FRONT,
		BACK, 
		INSERT,
		REMOVE,
		BEGIN,
		END,
		PUSH,
		POP,
		PEEK,
		CONTAINS,

		// Cast
		CAST_BOOL = 0xb0,
		CAST_CHAR,
		CAST_INT,
		CAST_FLOAT,
		CAST_STRING,
		CAST_ARRAY,

		// Type utils
		TYPEID = 0xc0,
		CLONE,

		// Structs
		MEMBER_READ = 0xd0,
		MEMBER_WRITE,		
	};
}