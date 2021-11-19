#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		
		ADD = 0x10, SUB, MLT, DIV, MOD, EQL, UEQL, SML, BGR, BGREQL, SMLEQL, NEG,
		NEWI = 0x30, NEWF, NEWU, TRUE, FALSE, NEWARR, NEWMAP, NVLL,
		JUMP = 0x40, LINK, RETURN, IF, ERROR,
		READ = 0x60, WRITE, SCRAP,
		OUT,
	};
}