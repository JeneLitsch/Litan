#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		
		ADD = 0x10, SUB, MLT, DIV, MOD,
		EQL, UEQL, SML, BGR, SMLEQL, BGREQL,

		NEG = 0x20, NOT, INC, DEC,
		
		NEWI = 0x30, NEWF, NEWU, ADDR, TRUE, FALSE, NEWARR, NVLL, CHAR,

		JUMP = 0x40, CALL, RETURN, IF, ERROR, EXIT,

		READ = 0x60, WRITE, SCRAP, MAKEVAR, 

		OUT = 0x70,

		ALLOC_STR = 0x80, ALLOC_ARR,
	};
}