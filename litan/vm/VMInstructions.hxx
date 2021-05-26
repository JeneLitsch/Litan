#pragma once
#include <cstdint>

// formats
// c,v,s 	-> 32 16 8 opcode(8)
// j 		-> 56      opcode(8)

enum class InstCode : std::uint8_t {
	EXIT = 0x00, SUSPEND, ERROR, 
	SCRAP = 0x03, CLEAR, PRINT, FETCH, 

	LOAD = 0x10, STORE, COPY, SIZE,	INIT,
	ADDI = 0x20, SUBI, MLTI, DIVI, POWI, MODI, CASTI,
	INC, DEC,
	ADDF = 0x30, SUBF, MLTF, DIVF, POWF, MODF, CASTF, 
	
	BITOR = 0x40, BITAND, BITXOR,
	LOGOR = 0x50, LOGAND, LOGXOR,

	EQLI = 0x60, SMLI, BGRI, SPSHI,
	EQLF = 0x70, SMLF, BGRF, SPSHF,


	CALL = 0x80, GOTO, RETURN, IFSK,
	
	NEWL = 0x90, NEWU,
	
	EXT0, EXT1, EXT2, EXT3, EXT4, EXT5, EXT6, EXT7,


	SYSC = 0xf8, ARRAY, LOOP
};

enum class ArrayFunct : std::uint8_t {
	NEW = 0x00, DEL,
	CLR = 0x10,
	GET = 0x20, SET,
	ADD = 0x30, POP,
	LEN = 0x40,
};

enum class LoopFunct : std::uint8_t {
	RANGE = 0x00, INF,
	CONT = 0x10, STOP,
	IDX = 0x20,
};