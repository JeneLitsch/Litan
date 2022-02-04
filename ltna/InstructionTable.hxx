#pragma once
#include <unordered_map>
#include <string_view>
#include <tuple>
#include "ltn/InstructionSet.hxx"
namespace ltn::a {
	
	using namespace std::string_view_literals;
	
	enum struct ArgFormat {
		NONE,
		UINT, UINTx2,
		INT,
		FLOAT,
		BYTE,
		CHAR,
		CHAR_4,
		CHAR_8,
	};
	
	enum class JumpFormat {
		ARG1, NONE
	};

	struct InstructionData {
		Inst opcode;
		std::size_t bytes = 1;
		ArgFormat argFormat = ArgFormat::NONE;
		JumpFormat jumpFormat = JumpFormat::NONE;
	};

	using InstructionTable = std::unordered_map<
		std::string_view,
		InstructionData>;
	
	const InstructionTable instructionTable{
		{"error", {Inst::ERROR}},
		{"exit", {Inst::EXIT}},
		{"state", {Inst::STATE}},

		// Binary operations
		{"add", {Inst::ADD}},
		{"sub", {Inst::SUB}},
		{"mlt", {Inst::MLT}},
		{"div", {Inst::DIV}},
		{"mod", {Inst::MOD}},
		{"eql", {Inst::EQL}},
		{"ueql", {Inst::UEQL}},
		{"sml", {Inst::SML}},
		{"bgr", {Inst::BGR}},
		{"smleql", {Inst::SMLEQL}},
		{"bgreql", {Inst::BGREQL}},
		{"shift_l", {Inst::SHIFT_L}},
		{"shift_r", {Inst::SHIFT_R}},

		// Unary operations
		{"neg", {Inst::NEG}},
		{"not", {Inst::NOT}},
		{"inc", {Inst::INC}},
		{"dec", {Inst::DEC}},

		// Values
		{"newu", {Inst::NEWU, 9, ArgFormat::UINT}},
		{"newi", {Inst::NEWI, 9, ArgFormat::INT}},
		{"newf", {Inst::NEWF, 9, ArgFormat::FLOAT}},
		{"true", {Inst::TRUE}},
		{"false", {Inst::FALSE}},
		{"null", {Inst::NVLL}},
		{"char", {Inst::CHAR, 2, ArgFormat::CHAR}},
		{"elem", {Inst::ELEM}},
		{"char_4", {Inst::CHAR_4, 5, ArgFormat::CHAR_4}},
		{"char_8", {Inst::CHAR_8, 9, ArgFormat::CHAR_8}},
		
		// Allocations
		{"newarr", {Inst::NEWARR}},
		{"newstr", {Inst::NEWSTR}},
		{"newout", {Inst::NEWOUT, 2, ArgFormat::BYTE}},
		{"newin", {Inst::NEWIN, 2, ArgFormat::BYTE}},
		{"newfx", {Inst::NEWFX, 17, ArgFormat::UINTx2, JumpFormat::ARG1}},
		{"newclock", {Inst::NEWCLOCK}},
		{"newstruct", {Inst::NEWSTRUCT}},
		{"newrange", {Inst::NEWRANGE}},

		// Control flow
		{"jump", {Inst::JUMP, 9, ArgFormat::UINT, JumpFormat::ARG1}},
		{"call", {Inst::CALL, 9, ArgFormat::UINT, JumpFormat::ARG1}},
		{"parameters", {Inst::PARAMETERS, 2, ArgFormat::BYTE}},
		{"return", {Inst::RETURN}},
		{"ifelse", {Inst::IF, 9, ArgFormat::UINT, JumpFormat::ARG1}},

		// Functional
		{"invoke", {Inst::INVOKE}},
		{"external", {Inst::EXTERNAL}},
		{"capture", {Inst::CAPTURE}},

		// Memory
		{"read", {Inst::READ}},
		{"write", {Inst::WRITE}},
		{"scrap", {Inst::SCRAP}},
		{"makevar", {Inst::MAKEVAR}},
		{"at", {Inst::AT}},
		{"at_write", {Inst::AT_WRITE}},
		{"read_x", {Inst::READ_X, 9, ArgFormat::UINT}},
		{"write_x", {Inst::WRITE_X, 9, ArgFormat::UINT}},
		{"read_0", {Inst::READ_0}},
		{"read_1", {Inst::READ_1}},
		{"read_2", {Inst::READ_2}},
		{"read_3", {Inst::READ_3}},
		{"write_0", {Inst::WRITE_0}},
		{"write_1", {Inst::WRITE_1}},
		{"write_2", {Inst::WRITE_2}},
		{"write_3", {Inst::WRITE_3}},

		// Io
		{"out", {Inst::OUT}},
		{"in_str", {Inst::IN_STR}},
		{"in_line", {Inst::IN_LINE}},
		{"in_int", {Inst::IN_INT}},
		{"in_float", {Inst::IN_FLOAT}},
		{"is_eof", {Inst::IS_EOF}},

		// Math
		{"min", {Inst::MIN}},
		{"max", {Inst::MAX}},
		{"round", {Inst::ROUND}},
		{"floor", {Inst::FLOOR}},
		{"ceil", {Inst::CEIL}},
		{"abs", {Inst::ABS}},
		{"hypot", {Inst::HYPOT}},
		{"sqrt", {Inst::SQRT}},
		{"log", {Inst::LOG}},
		{"ln", {Inst::LN}},
		{"pow", {Inst::POW}},

		{"sin", {Inst::SIN}},
		{"cos", {Inst::COS}},
		{"tan", {Inst::TAN}},

		// Array Utils
		{"size", {Inst::SIZE}},
		{"front", {Inst::FRONT}},
		{"back", {Inst::BACK}},
		{"insert_back", {Inst::INSERT_BACK}},
		{"insert_front", {Inst::INSERT_FRONT}},
		{"insert", {Inst::INSERT}},
		{"remove_back", {Inst::REMOVE_BACK}},
		{"remove_front", {Inst::REMOVE_FRONT}},
		{"remove", {Inst::REMOVE}},
		{"begin", {Inst::BEGIN}},
		{"end", {Inst::END}},

		// Chrono utils
		{"cast_int", {Inst::CAST_INT}},
		{"cast_float", {Inst::CAST_FLOAT}},
		{"cast_string", {Inst::CAST_STRING}},
		{"cast_bool", {Inst::CAST_BOOL}},
		{"cast_array", {Inst::CAST_ARRAY}},

		// Type utils
		{"typeid", {Inst::TYPEID}},

		{"member_read", {Inst::MEMBER_READ, 9, ArgFormat::UINT}},
		{"member_write", {Inst::MEMBER_WRITE, 9, ArgFormat::UINT}},
	};
}