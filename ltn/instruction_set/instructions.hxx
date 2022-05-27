#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include "stdxx/float64_t.hxx"
#include "args.hxx"
#include "opcodes.hxx"

namespace ltn::inst {
	template<OpCode OPCODE, typename Args = args::None>
	struct Base {
		inline constexpr static auto opcode = OPCODE;
		Args args;
	};



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



	struct Out     : Base<OpCode::OUT> {
		inline constexpr static auto name = "out";
	};

	struct Stylize : Base<OpCode::STYLIZE, args::Byte> {
		inline constexpr static auto name = "stylize";
	};

	struct CloseStream : Base<OpCode::CLOSE_STREAM, args::Byte> {
		inline constexpr static auto name = "close_stream";
	};

	struct InStr   : Base<OpCode::IN_STR> {
		inline constexpr static auto name = "in_str";
	};

	struct InLine  : Base<OpCode::IN_LINE> {
		inline constexpr static auto name = "in_line";
	};

	struct InBool  : Base<OpCode::IN_BOOL> {
		inline constexpr static auto name = "in_bool";
	};

	struct InChar  : Base<OpCode::IN_CHAR> {
		inline constexpr static auto name = "in_char";
	};

	struct InInt   : Base<OpCode::IN_INT> {
		inline constexpr static auto name = "in_int";
	};

	struct InFloat : Base<OpCode::IN_FLOAT> {
		inline constexpr static auto name = "in_float";
	};

	struct InAll   : Base<OpCode::IN_ALL> {
		inline constexpr static auto name = "in_all";
	};

	struct IsEof   : Base<OpCode::IS_EOF> {
		inline constexpr static auto name = "is_eof";
	};

	struct IsGood  : Base<OpCode::IS_GOOD> {
		inline constexpr static auto name = "is_good";
	};



	struct Min     : Base<OpCode::MIN> {
		inline constexpr static auto name = "min";
	};

	struct Max     : Base<OpCode::MAX> {
		inline constexpr static auto name = "max";
	};

	struct Round   : Base<OpCode::ROUND> {
		inline constexpr static auto name = "round";
	};

	struct Floor   : Base<OpCode::FLOOR> {
		inline constexpr static auto name = "floor";
	};

	struct Ceil    : Base<OpCode::CEIL> {
		inline constexpr static auto name = "ceil";
	};

	struct Abs     : Base<OpCode::ABS> {
		inline constexpr static auto name = "abs";
	};

	struct Hypot   : Base<OpCode::HYPOT> {
		inline constexpr static auto name = "hypot";
	};

	struct Sqrt    : Base<OpCode::SQRT> {
		inline constexpr static auto name = "sqrt";
	};

	struct Log     : Base<OpCode::LOG> {
		inline constexpr static auto name = "log";
	};

	struct Ln      : Base<OpCode::LN> {
		inline constexpr static auto name = "ln";
	};

	struct Pow     : Base<OpCode::POW> {
		inline constexpr static auto name = "pow";
	};

	struct Sin     : Base<OpCode::SIN> {
		inline constexpr static auto name = "sin";
	};
	struct Cos     : Base<OpCode::COS> {
		inline constexpr static auto name = "cos";
	};
	struct Tan     : Base<OpCode::TAN> {
		inline constexpr static auto name = "tan";
	};



	struct Bitand  : Base<OpCode::BITAND> {
		inline constexpr static auto name = "bitand";
	};

	struct Bitor   : Base<OpCode::BITOR> {
		inline constexpr static auto name = "bitor";
	};
	
	struct Bitxor  : Base<OpCode::BITXOR> {
		inline constexpr static auto name = "bitxor";
	};

	struct Bitnot  : Base<OpCode::BITNOT> {
		inline constexpr static auto name = "bitnot";
	};


	struct Size    : Base<OpCode::SIZE> {
		inline constexpr static auto name = "size";
	};

	struct At      : Base<OpCode::AT> {
		inline constexpr static auto name = "at";
	};

	struct AtWrite : Base<OpCode::AT_WRITE> {
		inline constexpr static auto name = "at_write";
	};

	struct Front   : Base<OpCode::FRONT> {
		inline constexpr static auto name = "front";
	};

	struct Back    : Base<OpCode::BACK> {
		inline constexpr static auto name = "back";
	};

	struct Insert  : Base<OpCode::INSERT, args::Byte> {
		inline constexpr static auto name = "insert";
	};

	struct Remove  : Base<OpCode::REMOVE, args::Byte> {
		inline constexpr static auto name = "remove";
	};

	struct Begin   : Base<OpCode::BEGIN> {
		inline constexpr static auto name = "begin";
	};

	struct End     : Base<OpCode::END> {
		inline constexpr static auto name = "end";
	};

	struct Push    : Base<OpCode::PUSH> {
		inline constexpr static auto name = "push";
	};

	struct Pop     : Base<OpCode::POP> {
		inline constexpr static auto name = "pop";
	};

	struct Peek    : Base<OpCode::PEEK> {
		inline constexpr static auto name = "peek";
	};

	struct Contains: Base<OpCode::CONTAINS> {
		inline constexpr static auto name = "contains";
	};
	


	struct CastBool   : Base<OpCode::CAST_BOOL> {
		inline constexpr static auto name = "cast_bool";
	};

	struct CastChar   : Base<OpCode::CAST_CHAR> {
		inline constexpr static auto name = "cast_char";
	};

	struct CastInt    : Base<OpCode::CAST_INT> {
		inline constexpr static auto name = "cast_int";
	};

	struct CastFloat  : Base<OpCode::CAST_FLOAT> {
		inline constexpr static auto name = "cast_float";
	};

	struct CastString : Base<OpCode::CAST_STRING> {
		inline constexpr static auto name = "cast_string";
	};

	struct CastArray  : Base<OpCode::CAST_ARRAY> {
		inline constexpr static auto name = "cast_array";
	};



	struct TypeId     : Base<OpCode::TYPEID> {
		inline constexpr static auto name = "typeid";
	};

	struct Clone      : Base<OpCode::CLONE> {
		inline constexpr static auto name = "clone";
	};
	


	struct MemberRead  : Base<OpCode::MEMBER_READ, args::Uint64> {
		inline constexpr static auto name = "member_read";
	};

	struct MemberWrite : Base<OpCode::MEMBER_WRITE, args::Uint64> {
		inline constexpr static auto name = "member_write";
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