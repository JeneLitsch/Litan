#pragma once
#include <cstdint>
namespace ltn {
	enum class OpCode : std::uint8_t {
		// System
		EXIT = 0x00,
		ERROR,
		TRY,
		THROW,
		BUILD_IN,
		
		// Binary arithmetic
		ADD = 0x10,
		SUB,
		MLT,
		DIV,
		MOD,
		POW,


		// Comparisons
		EQL = 0x18,
		UEQL,
		LT,
		GT,
		LTEQL,
		GTEQL,
		
		// Shift
		SHIFT_L,
		SHIFT_R,

		// Unary operators
		NEG = 0x20,
		NOT,
		INC,
		DEC,
		DEREF,

		COMP = 0x28,

		// Primitives
		NEWI = 0x30,
		NEWF,
		NEWC,
		TRUE,
		FALSE,
		NVLL,
		NEWI_SMALL,

		// Controlflow and functions
		JUMP = 0x40,
		CALL,
		RETURN,
		IF,
		INVOKE,
		INVOKE_VARIADIC,
		CAPTURE,
		FOR_NEXT,

		// Allocations
		NEWARR = 0x50,
		NEWSTR,
		NEWFX,
		NEWCLOCK,
		NEWSTRUCT,
		NEWSTACK,
		NEWQUEUE,
		NEWMAP,
		NEWTUPLE,
		NEWTYPE,

		// Stack read/write
		SCRAP = 0x60,
		DUPLICATE,
		READ_X,
		WRITE_X,
		SWAP,
		UNPACK,

		// Fast stack read/write
		READ_0 = 0x68,
		READ_1,
		READ_2,
		READ_3, 
		WRITE_0,
		WRITE_1,
		WRITE_2,
		WRITE_3,

		// Constants
		NEWI_CONST_0 = 0x70,
		NEWI_CONST_1,
		NEWI_CONST_2,

		// Bitwise
		BITAND = 0x90,
		BITOR,
		BITXOR,
		BITNOT,

		// Collections and containers
		AT = 0xa0,
		AT_WRITE,
		ITER,

		// Cast
		CAST_BOOL = 0xb0,

		// Structs
		MEMBER_READ = 0xd0,
		MEMBER_WRITE,
		GLOBAL_READ,
		GLOBAL_WRITE,
	};
}