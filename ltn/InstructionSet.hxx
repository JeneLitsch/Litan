#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		
		ADD = 0x10, SUB, MLT, DIV, MOD,
		EQL, UEQL, SML, BGR, SMLEQL, BGREQL,
		SHIFT_L, SHIFT_R,

		NEG = 0x20, NOT, INC, DEC,
		
		NEWI = 0x30, NEWF, NEWU, ADDR, TRUE, FALSE, NEWARR, NEWSTR, NEWOUT_STD, NVLL, CHAR, ELEM,

		JUMP = 0x40, CALL, RETURN, IF, ERROR, EXIT,

		READ = 0x60, WRITE, SCRAP, MAKEVAR, AT, AT_WRITE,

		OUT = 0x70,
	};
}