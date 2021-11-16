#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		
		ADDI = 0x10, SUBI, MLTI, DIVI, MODI,
		ADDF = 0x20, SUBF, MLTF, DIVF, MODF,
		NEWI = 0x30, NEWF, NEWU, READ, WRITE, SCRAP,
		GOTO = 0x40, CALL, RETURN,
		OUT,
	};
}