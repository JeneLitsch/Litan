#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include "stdxx/float64_t.hxx"
#include "args.hxx"
#include "opcodes.hxx"

namespace ltn::inst {
	struct Label {
		args::Target args;
		inline constexpr static auto name = ":";
	};



	struct Exit {
		inline constexpr static auto opcode = OpCode::EXIT;
		inline constexpr static auto name = "exit";
		args::None args;
	};

	struct Error {
		inline constexpr static auto opcode = OpCode::ERROR;
		inline constexpr static auto name = "error";
		args::None args;
	};

	struct State {
		inline constexpr static auto opcode = OpCode::STATE;
		inline constexpr static auto name = "state";
		args::None args;
	};

	struct Try {
		inline constexpr static auto opcode = OpCode::TRY;
		inline constexpr static auto name = "try";
		args::Jump args;
	};

	struct Throw {
		inline constexpr static auto opcode = OpCode::THROW;
		inline constexpr static auto name = "throw";
		args::None args;
	};

	struct BuildIn {
		inline constexpr static auto opcode = OpCode::BUILD_IN;
		inline constexpr static auto name = "build_in";
		args::Uint16 args;
	};
	


	struct Add {
		inline constexpr static auto opcode = OpCode::ADD;
		inline constexpr static auto name = "add";
		args::None args;
	};

	struct Sub {
		inline constexpr static auto opcode = OpCode::SUB;
		inline constexpr static auto name = "sub";
		args::None args;
	};

	struct Mlt {
		inline constexpr static auto opcode = OpCode::MLT;
		inline constexpr static auto name = "mlt";
		args::None args;
	};

	struct Div {
		inline constexpr static auto opcode = OpCode::DIV;
		inline constexpr static auto name = "div";
		args::None args;
	};

	struct Mod {
		inline constexpr static auto opcode = OpCode::MOD;
		inline constexpr static auto name = "mod";
		args::None args;
	};


	
	struct Eql {
		inline constexpr static auto opcode = OpCode::EQL;
		inline constexpr static auto name = "eql";
		args::None args;
	};

	struct Ueql {
		inline constexpr static auto opcode = OpCode::UEQL;
		inline constexpr static auto name = "ueql";
		args::None args;
	};

	struct Sml {
		inline constexpr static auto opcode = OpCode::SML;
		inline constexpr static auto name = "sml";
		args::None args;
	};

	struct Bgr {
		inline constexpr static auto opcode = OpCode::BGR;
		inline constexpr static auto name = "bgr";
		args::None args;
	};

	struct Smleql {
		inline constexpr static auto opcode = OpCode::SMLEQL;
		inline constexpr static auto name = "smleql";
		args::None args;
	};

	struct Bgreql {
		inline constexpr static auto opcode = OpCode::BGREQL;
		inline constexpr static auto name = "bgreql";
		args::None args;
	};



	struct ShiftL {
		inline constexpr static auto opcode = OpCode::SHIFT_L;
		inline constexpr static auto name = "shift_l";
		args::None args;
	};
	
	struct ShiftR {
		inline constexpr static auto opcode = OpCode::SHIFT_R;
		inline constexpr static auto name = "shift_r";
		args::None args;
	};
	


	struct Neg {
		inline constexpr static auto opcode = OpCode::NEG;
		inline constexpr static auto name = "neg";
		args::None args;
	};

	struct Not {
		inline constexpr static auto opcode = OpCode::NOT;
		inline constexpr static auto name = "not";
		args::None args;
	};

	struct Inc {
		inline constexpr static auto opcode = OpCode::INC;
		inline constexpr static auto name = "inc";
		args::None args;
	};

	struct Dec {
		inline constexpr static auto opcode = OpCode::DEC;
		inline constexpr static auto name = "dec";
		args::None args;
	};
	
	struct Comp  {
		inline constexpr static auto opcode = OpCode::COMP;
		inline constexpr static auto name = "comp";
		args::None args;
	};

	struct Approx {
		inline constexpr static auto opcode = OpCode::APPROX;
		inline constexpr static auto name = "approx";
		args::None args;
	};

	struct Between {
		inline constexpr static auto opcode = OpCode::BETWEEN;
		inline constexpr static auto name = "between";
		args::None args;
	};



	struct Newu {
		inline constexpr static auto opcode = OpCode::NEWU;
		inline constexpr static auto name = "newu";
		args::Uint64 args;
	};

	struct Newi {
		inline constexpr static auto opcode = OpCode::NEWI;
		inline constexpr static auto name = "newi";
		args::Int64 args;
	};

	struct Newf {
		inline constexpr static auto opcode = OpCode::NEWF;
		inline constexpr static auto name = "newf";
		args::Float args;
	};

	struct Newc {
		inline constexpr static auto opcode = OpCode::NEWC;
		inline constexpr static auto name = "newc";
		args::Byte args;
	};

	struct True {
		inline constexpr static auto opcode = OpCode::TRUE;
		inline constexpr static auto name = "true";
		args::None args;
	};

	struct False {
		inline constexpr static auto opcode = OpCode::FALSE;
		inline constexpr static auto name = "false";
		args::None args;
	};

	struct Null {
		inline constexpr static auto opcode = OpCode::NVLL;
		inline constexpr static auto name = "null";
		args::None args;
	};



	struct Newarr {
		inline constexpr static auto opcode = OpCode::NEWARR;
		inline constexpr static auto name = "newarr";
		args::Uint64 args;
	};

	struct Newstr {
		inline constexpr static auto opcode = OpCode::NEWSTR;
		inline constexpr static auto name = "newstr";
		args::Uint64_BytexX args;
	};
	
	struct Newout {
		inline constexpr static auto opcode = OpCode::NEWOUT;
		inline constexpr static auto name = "newout";
		args::Byte args;
	};

	struct Newin {
		inline constexpr static auto opcode = OpCode::NEWIN;
		inline constexpr static auto name = "newin";
		args::Byte args;
	};

	struct Newfx {
		inline constexpr static auto opcode = OpCode::NEWFX;
		inline constexpr static auto name = "newfx";
		args::Jump_Uint64 args;
	};

	struct Newclock {
		inline constexpr static auto opcode = OpCode::NEWCLOCK;
		inline constexpr static auto name = "newclock";
		args::None args;
	};

	struct Newstruct {
		inline constexpr static auto opcode = OpCode::NEWSTRUCT;
		inline constexpr static auto name = "newstruct";
		args::None args;
	};

	struct Newrange {
		inline constexpr static auto opcode = OpCode::NEWRANGE;
		inline constexpr static auto name = "newrange";
		args::None args;
	};

	struct Newstack {
		inline constexpr static auto opcode = OpCode::NEWSTACK;
		inline constexpr static auto name = "newstack";
		args::None args;
	};

	struct Newqueue {
		inline constexpr static auto opcode = OpCode::NEWQUEUE;
		inline constexpr static auto name = "newqueue";
		args::None args;
	};

	struct Newmap {
		inline constexpr static auto opcode = OpCode::NEWMAP;
		inline constexpr static auto name = "newmap";
		args::None args;
	};

	struct Newrng {
		inline constexpr static auto opcode = OpCode::NEWRNG;
		inline constexpr static auto name = "newrng";
		args::Byte args;
	};


	struct Jump {
		inline constexpr static auto opcode = OpCode::JUMP;
		inline constexpr static auto name = "jump";
		args::Jump args;
	};

	struct Call {
		inline constexpr static auto opcode = OpCode::CALL;
		inline constexpr static auto name = "call";
		args::Jump args;
	};

	struct Params {
		inline constexpr static auto opcode = OpCode::PARAMETERS;
		inline constexpr static auto name = "parameters";
		args::Byte args;
	};

	struct Return {
		inline constexpr static auto opcode = OpCode::RETURN;
		inline constexpr static auto name = "return";
		args::None args;
	};

	struct Ifelse {
		inline constexpr static auto opcode = OpCode::IF;
		inline constexpr static auto name = "ifelse";
		args::Jump args;
	};
	


	struct Invoke {
		inline constexpr static auto opcode = OpCode::INVOKE;
		inline constexpr static auto name = "invoke";
		args::None args;
	};
	
	struct External {
		inline constexpr static auto opcode = OpCode::EXTERNAL;
		inline constexpr static auto name = "external";
		args::None args;
	};

	struct Capture {
		inline constexpr static auto opcode = OpCode::CAPTURE;
		inline constexpr static auto name = "capture";
		args::None args;
	};
	


	struct Read {
		inline constexpr static auto opcode = OpCode::READ;
		inline constexpr static auto name = "read";
		args::None args;
	};

	struct Write {
		inline constexpr static auto opcode = OpCode::WRITE;
		inline constexpr static auto name = "write";
		args::None args;
	};

	struct Scrap {
		inline constexpr static auto opcode = OpCode::SCRAP;
		inline constexpr static auto name = "scrap";
		args::None args;
	};

	struct Duplicate {
		inline constexpr static auto opcode = OpCode::DUPLICATE;
		inline constexpr static auto name = "duplicate";
		args::None args;
	};

	struct Makevar {
		inline constexpr static auto opcode = OpCode::MAKEVAR;
		inline constexpr static auto name = "makevar";
		args::None args;
	};

	struct Readx {
		inline constexpr static auto opcode = OpCode::READ_X;
		inline constexpr static auto name = "read_x";
		args::Uint64 args;
	};

	struct Writex {
		inline constexpr static auto opcode = OpCode::WRITE_X;
		inline constexpr static auto name = "write_x";
		args::Uint64 args;
	};

	struct Swap {
		inline constexpr static auto opcode = OpCode::SWAP;
		inline constexpr static auto name = "swap";
		args::None args;
	};



	struct Read0 {
		inline constexpr static auto opcode = OpCode::READ_0;
		inline constexpr static auto name = "read_0";
		args::None args;
	};

	struct Read1 {
		inline constexpr static auto opcode = OpCode::READ_1;
		inline constexpr static auto name = "read_1";
		args::None args;
	};

	struct Read2 {
		inline constexpr static auto opcode = OpCode::READ_2;
		inline constexpr static auto name = "read_2";
		args::None args;
	};

	struct Read3 {
		inline constexpr static auto opcode = OpCode::READ_3;
		inline constexpr static auto name = "read_3";
		args::None args;
	};



	struct Write0 {
		inline constexpr static auto opcode = OpCode::WRITE_0;
		inline constexpr static auto name = "write_0";
		args::None args;
	};

	struct Write1 {
		inline constexpr static auto opcode = OpCode::WRITE_1;
		inline constexpr static auto name = "write_1";
		args::None args;
	};

	struct Write2 {
		inline constexpr static auto opcode = OpCode::WRITE_2;
		inline constexpr static auto name = "write_2";
		args::None args;
	};

	struct Write3 {
		inline constexpr static auto opcode = OpCode::WRITE_3;
		inline constexpr static auto name = "write_3";
		args::None args;
	};



	struct Out {
		inline constexpr static auto opcode = OpCode::OUT;
		inline constexpr static auto name = "out";
		args::None args;
	};

	struct Stylize {
		inline constexpr static auto opcode = OpCode::STYLIZE;
		inline constexpr static auto name = "stylize";
		args::Byte args;
	};

	struct CloseStream {
		inline constexpr static auto opcode = OpCode::CLOSE_STREAM;
		inline constexpr static auto name = "close_stream";
		args::Byte args;
	};

	struct InStr {
		inline constexpr static auto opcode = OpCode::IN_STR;
		inline constexpr static auto name = "in_str";
		args::None args;
	};

	struct InLine {
		inline constexpr static auto opcode = OpCode::IN_LINE;
		inline constexpr static auto name = "in_line";
		args::None args;
	};

	struct InBool {
		inline constexpr static auto opcode = OpCode::IN_BOOL;
		inline constexpr static auto name = "in_bool";
		args::None args;
	};

	struct InChar {
		inline constexpr static auto opcode = OpCode::IN_CHAR;
		inline constexpr static auto name = "in_char";
		args::None args;
	};

	struct InInt {
		inline constexpr static auto opcode = OpCode::IN_INT;
		inline constexpr static auto name = "in_int";
		args::None args;
	};

	struct InFloat {
		inline constexpr static auto opcode = OpCode::IN_FLOAT;
		inline constexpr static auto name = "in_float";
		args::None args;
	};

	struct InAll {
		inline constexpr static auto opcode = OpCode::IN_ALL;
		inline constexpr static auto name = "in_all";
		args::None args;
	};

	struct IsEof {
		inline constexpr static auto opcode = OpCode::IS_EOF;
		inline constexpr static auto name = "is_eof";
		args::None args;
	};

	struct IsGood {
		inline constexpr static auto opcode = OpCode::IS_GOOD;
		inline constexpr static auto name = "is_good";
		args::None args;
	};



	struct Min {
		inline constexpr static auto opcode = OpCode::MIN;
		inline constexpr static auto name = "min";
		args::None args;
	};

	struct Max {
		inline constexpr static auto opcode = OpCode::MAX;
		inline constexpr static auto name = "max";
		args::None args;
	};

	struct Round {
		inline constexpr static auto opcode = OpCode::ROUND;
		inline constexpr static auto name = "round";
		args::None args;
	};

	struct Floor {
		inline constexpr static auto opcode = OpCode::FLOOR;
		inline constexpr static auto name = "floor";
		args::None args;
	};

	struct Ceil {
		inline constexpr static auto opcode = OpCode::CEIL;
		inline constexpr static auto name = "ceil";
		args::None args;
	};

	struct Abs {
		inline constexpr static auto opcode = OpCode::ABS;
		inline constexpr static auto name = "abs";
		args::None args;
	};

	struct Hypot {
		inline constexpr static auto opcode = OpCode::HYPOT;
		inline constexpr static auto name = "hypot";
		args::None args;
	};

	struct Sqrt {
		inline constexpr static auto opcode = OpCode::SQRT;
		inline constexpr static auto name = "sqrt";
		args::None args;
	};

	struct Log {
		inline constexpr static auto opcode = OpCode::LOG;
		inline constexpr static auto name = "log";
		args::None args;
	};

	struct Ln {
		inline constexpr static auto opcode = OpCode::LN;
		inline constexpr static auto name = "ln";
		args::None args;
	};

	struct Pow {
		inline constexpr static auto opcode = OpCode::POW;
		inline constexpr static auto name = "pow";
		args::None args;
	};

	struct Sin {
		inline constexpr static auto opcode = OpCode::SIN;
		inline constexpr static auto name = "sin";
		args::None args;
	};

	struct Cos {
		inline constexpr static auto opcode = OpCode::COS;
		inline constexpr static auto name = "cos";
		args::None args;
	};
	
	struct Tan {
		inline constexpr static auto opcode = OpCode::TAN;
		inline constexpr static auto name = "tan";
		args::None args;
	};



	struct Bitand {
		inline constexpr static auto opcode = OpCode::BITAND;
		inline constexpr static auto name = "bitand";
		args::None args;
	};

	struct Bitor {
		inline constexpr static auto opcode = OpCode::BITOR;
		inline constexpr static auto name = "bitor";
		args::None args;
	};
	
	struct Bitxor {
		inline constexpr static auto opcode = OpCode::BITXOR;
		inline constexpr static auto name = "bitxor";
		args::None args;
	};

	struct Bitnot {
		inline constexpr static auto opcode = OpCode::BITNOT;
		inline constexpr static auto name = "bitnot";
		args::None args;
	};


	struct Size {
		inline constexpr static auto opcode = OpCode::SIZE;
		inline constexpr static auto name = "size";
		args::None args;
	};

	struct At {
		inline constexpr static auto opcode = OpCode::AT;
		inline constexpr static auto name = "at";
		args::None args;
	};

	struct AtWrite {
		inline constexpr static auto opcode = OpCode::AT_WRITE;
		inline constexpr static auto name = "at_write";
		args::None args;
	};

	struct Front {
		inline constexpr static auto opcode = OpCode::FRONT;
		inline constexpr static auto name = "front";
		args::None args;
	};

	struct Back {
		inline constexpr static auto opcode = OpCode::BACK;
		inline constexpr static auto name = "back";
		args::None args;
	};

	struct Insert {
		inline constexpr static auto opcode = OpCode::INSERT;
		inline constexpr static auto name = "insert";
		args::Byte args;
	};

	struct Remove {
		inline constexpr static auto opcode = OpCode::REMOVE;
		inline constexpr static auto name = "remove";
		args::Byte args;
	};

	struct Begin    {
		inline constexpr static auto opcode = OpCode::BEGIN;
		inline constexpr static auto name = "begin";
		args::None args;
	};

	struct End {
		inline constexpr static auto opcode = OpCode::END;
		inline constexpr static auto name = "end";
		args::None args;
	};

	struct Push {
		inline constexpr static auto opcode = OpCode::PUSH;
		inline constexpr static auto name = "push";
		args::None args;
	};

	struct Pop {
		inline constexpr static auto opcode = OpCode::POP;
		inline constexpr static auto name = "pop";
		args::None args;
	};

	struct Peek     {
		inline constexpr static auto opcode = OpCode::PEEK;
		inline constexpr static auto name = "peek";
		args::None args;
	};

	struct Contains {
		inline constexpr static auto opcode = OpCode::CONTAINS;
		inline constexpr static auto name = "contains";
		args::None args;
	};
	


	struct CastBool {
		inline constexpr static auto opcode = OpCode::CAST_BOOL;
		inline constexpr static auto name = "cast_bool";
		args::None args;
	};

	struct CastChar {
		inline constexpr static auto opcode = OpCode::CAST_CHAR;
		inline constexpr static auto name = "cast_char";
		args::None args;
	};

	struct CastInt {
		inline constexpr static auto opcode = OpCode::CAST_INT;
		inline constexpr static auto name = "cast_int";
		args::None args;
	};

	struct CastFloat {
		inline constexpr static auto opcode = OpCode::CAST_FLOAT;
		inline constexpr static auto name = "cast_float";
		args::None args;
	};

	struct CastString {
		inline constexpr static auto opcode = OpCode::CAST_STRING;
		inline constexpr static auto name = "cast_string";
		args::None args;
	};

	struct CastArray {
		inline constexpr static auto opcode = OpCode::CAST_ARRAY;
		inline constexpr static auto name = "cast_array";
		args::None args;
	};



	struct TypeId {
		inline constexpr static auto opcode = OpCode::TYPEID;
		inline constexpr static auto name = "typeid";
		args::None args;
	};

	struct Clone {
		inline constexpr static auto opcode = OpCode::CLONE;
		inline constexpr static auto name = "clone";
		args::None args;
	};
	


	struct MemberRead {
		inline constexpr static auto opcode = OpCode::MEMBER_READ;
		inline constexpr static auto name = "member_read";
		args::Uint64 args;
	};

	struct MemberWrite {
		inline constexpr static auto opcode = OpCode::MEMBER_WRITE;
		inline constexpr static auto name = "member_write";
		args::Uint64 args;
	};



	using Instruction = std::variant<
		Label,
		
		Exit,
		Error,
		State,
		Try,
		Throw,
		BuildIn,
		
		Add,
		Sub,
		Mlt,
		Div,
		Mod,
		
		Eql,
		Ueql,
		Sml,
		Bgr,
		Smleql,
		Bgreql,
		
		ShiftL,
		ShiftR,
		
		Neg,
		Not,
		Inc,
		Dec,
		
		Comp,
		Approx,
		Between, 
		
		Newu,
		Newi,
		Newf,
		Newc,
		True,
		False,
		Null,
		
		Newarr,
		Newstr,
		Newout,
		Newin,
		Newfx,
		Newclock,
		Newstruct,
		Newrange,
		Newstack,
		Newqueue,
		Newmap,
		Newrng,
		
		Jump,
		Call,
		Params,
		Return,
		Ifelse,
		
		Invoke,
		External,
		Capture,
		
		Read,
		Write,
		Scrap,
		Duplicate,
		Makevar,
		Readx,
		Writex,
		Swap,
		
		Read0,
		Read1,
		Read2,
		Read3,
		
		Write0,
		Write1,
		Write2,
		Write3,
		
		Out,
		Stylize,
		CloseStream,
		InStr,
		InLine,
		InBool,
		InChar,
		InInt,
		InFloat,
		InAll,
		IsEof,
		IsGood,
		
		Min,
		Max,
		Round,
		Floor,
		Ceil,
		Abs,
		Hypot,
		Sqrt,
		Log,
		Ln,
		Pow,

		Sin,
		Cos,
		Tan,
		
		Bitand,
		Bitor,
		Bitxor,
		Bitnot,
		
		Size,
		At,
		AtWrite,
		Front,
		Back,
		Insert,
		Remove,
		Begin,
		End,
		Push,
		Pop,
		Peek,
		Contains,
		
		CastChar,
		CastBool,
		CastInt,
		CastFloat,
		CastString,
		CastArray,
		
		TypeId,
		Clone,
		
		MemberRead,
		MemberWrite
	>;
}