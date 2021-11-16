#pragma once
#include <cstdint>
namespace ltn {
	enum class Inst : std::uint8_t {
		
		ADDI = 0x10, SUBI, MLTI, DIVI, MODI, EQLI, UEQLI, SMLI, BGRI, BGREQLI, SMLEQLI,  
		ADDF = 0x20, SUBF, MLTF, DIVF, MODF, EQLF, UEQLF, SMLF, BGRF, BGREQLF, SMLEQLF,
		NEWI = 0x30, NEWF, NEWU, READ, WRITE, SCRAP,
		GOTO = 0x40, CALL, RETURN,
		OUT,
	};
}