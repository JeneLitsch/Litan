#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		
		ADDI = 0x10, SUBI, MLTI, DIVI, MODI, EQLI, UEQLI, SMLI, BGRI, BGREQLI, SMLEQLI, NEGI,
		ADDF = 0x20, SUBF, MLTF, DIVF, MODF, EQLF, UEQLF, SMLF, BGRF, BGREQLF, SMLEQLF, NEGF,
		NEWI = 0x30, NEWF, NEWU, TRUE, FALSE, READ, WRITE, SCRAP,
		JUMP = 0x40, LINK, RETURN, IF, ERROR,
		OUT,
	};
}