#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include "stdxx/float64_t.hxx"
#include "stdxx/string_literal.hxx"
#include "args.hxx"
#include "ltn/opcodes.hxx"

namespace ltn::inst {
	struct InstCore {
		virtual ~InstCore() = default;
		virtual args::Args get_args() const = 0;
	};



	struct Label : InstCore {
		Label(const std::string & str = "") : InstCore{}, args{str} {} 
		args::Target args;
		inline constexpr static auto name = ":";
		virtual args::Args get_args() const override {
			return args;
		}
	};



	struct ExecInst : InstCore {
		virtual const char * get_name() const = 0;
		virtual OpCode get_opcode() const = 0;
	};



	template<OpCode OPCODE, stx::string_literal NAME, typename Args>
	struct GenericInst : ExecInst {
		inline constexpr static auto opcode = OPCODE;
		inline constexpr static auto name = NAME;

		GenericInst(auto ... x) : args{x...} {}
		GenericInst(auto x) : args{x} {}

		virtual const char * get_name() const override {
			return name.c_str();
		}

		virtual OpCode get_opcode() const override {
			return opcode;
		}

		virtual args::Args get_args() const override {
			return args;
		}

		Args args;

		using ArgsT = Args;
	};


	using Exit = GenericInst<OpCode::EXIT, "exit", args::None>;
	using Error = GenericInst<OpCode::ERROR, "error", args::None>;
	using State = GenericInst<OpCode::STATE, "state", args::None>;
	using Try = GenericInst<OpCode::TRY, "try", args::Jump>;
	using Throw = GenericInst<OpCode::THROW, "throw", args::None>;
	using BuildIn = GenericInst<OpCode::BUILD_IN, "build_in", args::Uint16>;
	
	using Add = GenericInst<OpCode::ADD, "add", args::None>;
	using Sub = GenericInst<OpCode::SUB, "sub", args::None>;
	using Mlt = GenericInst<OpCode::MLT, "mlt", args::None>;
	using Div = GenericInst<OpCode::DIV, "div", args::None>;
	using Mod = GenericInst<OpCode::MOD, "mod", args::None>;

	using Eql = GenericInst<OpCode::EQL, "eql", args::None>;
	using Ueql = GenericInst<OpCode::UEQL, "ueql", args::None>;
	using Sml = GenericInst<OpCode::SML, "sml", args::None>;
	using Bgr = GenericInst<OpCode::BGR, "bgr", args::None>;
	using Smleql = GenericInst<OpCode::SMLEQL, "smleql", args::None>;
	using Bgreql = GenericInst<OpCode::BGREQL, "bgreql", args::None>;

	using ShiftL = GenericInst<OpCode::SHIFT_L, "shift_l", args::None>;
	using ShiftR = GenericInst<OpCode::SHIFT_R, "shift_r", args::None>;

	using Neg = GenericInst<OpCode::NEG, "neg", args::None>;
	using Not = GenericInst<OpCode::NOT, "not", args::None>;
	using Inc = GenericInst<OpCode::INC, "inc", args::None>;
	using Dec = GenericInst<OpCode::DEC, "dec", args::None>;

	using Comp = GenericInst<OpCode::COMP, "comp", args::None>;
	using Between = GenericInst<OpCode::BETWEEN, "between", args::None>;

	using Newu = GenericInst<OpCode::NEWU, "newu", args::Uint64>;
	using Newi = GenericInst<OpCode::NEWI, "newi", args::Int64>;
	using Newf = GenericInst<OpCode::NEWF, "newf", args::Float>;
	using Newc = GenericInst<OpCode::NEWC, "newc", args::Byte>;
	using True = GenericInst<OpCode::TRUE, "true", args::None>;
	using False = GenericInst<OpCode::FALSE, "false", args::None>;
	using Null = GenericInst<OpCode::NVLL, "null", args::None>;

	using Newarr = GenericInst<OpCode::NEWARR, "newarr", args::Uint64>;
	using Newstr = GenericInst<OpCode::NEWSTR, "newstr", args::Uint64_BytexX>;
	using Newout = GenericInst<OpCode::NEWOUT, "newout", args::Byte>;
	using Newin = GenericInst<OpCode::NEWIN, "newin", args::Byte>;
	using Newfx = GenericInst<OpCode::NEWFX, "newfx", args::Jump_Uint64>;
	using Newclock = GenericInst<OpCode::NEWCLOCK, "newclock", args::None>;
	using Newstruct = GenericInst<OpCode::NEWSTRUCT, "newstruct", args::None>;
	using Newrange = GenericInst<OpCode::NEWRANGE, "newrange", args::None>;
	using Newstack = GenericInst<OpCode::NEWSTACK, "newstack", args::None>;
	using Newqueue = GenericInst<OpCode::NEWQUEUE, "newqueue", args::None>;
	using Newmap = GenericInst<OpCode::NEWMAP, "newmap", args::None>;
	using Newrng = GenericInst<OpCode::NEWRNG, "newrng", args::Byte>;

	using Jump = GenericInst<OpCode::JUMP, "jump", args::Jump>;
	using Call = GenericInst<OpCode::CALL, "call", args::Jump>;
	using Params = GenericInst<OpCode::PARAMETERS, "parameters", args::Byte>;
	using Return = GenericInst<OpCode::RETURN, "return", args::None>;
	using Ifelse = GenericInst<OpCode::IF, "ifelse", args::Jump>;
	
	using Invoke = GenericInst<OpCode::INVOKE, "invoke", args::None>;
	using External = GenericInst<OpCode::EXTERNAL, "external", args::None>;
	using Capture = GenericInst<OpCode::CAPTURE, "capture", args::None>;

	using Read = GenericInst<OpCode::READ, "read", args::None>;
	using Write = GenericInst<OpCode::WRITE, "write", args::None>;
	using Scrap = GenericInst<OpCode::SCRAP, "scrap", args::None>;
	using Duplicate = GenericInst<OpCode::DUPLICATE, "duplicate", args::None>;
	using Makevar = GenericInst<OpCode::MAKEVAR, "makevar", args::None>;

	using Readx = GenericInst<OpCode::READ_X, "read_x", args::Uint64>;
	using Writex = GenericInst<OpCode::WRITE_X, "write_x", args::Uint64>;
	using Swap = GenericInst<OpCode::SWAP, "swap", args::None>;

	using Read0 = GenericInst<OpCode::READ_0, "read_0", args::None>;
	using Read1 = GenericInst<OpCode::READ_1, "read_1", args::None>;
	using Read2 = GenericInst<OpCode::READ_2, "read_2", args::None>;
	using Read3 = GenericInst<OpCode::READ_3, "read_3", args::None>;

	using Write0 = GenericInst<OpCode::WRITE_0, "write_0", args::None>;
	using Write1 = GenericInst<OpCode::WRITE_1, "write_1", args::None>;
	using Write2 = GenericInst<OpCode::WRITE_2, "write_2", args::None>;
	using Write3 = GenericInst<OpCode::WRITE_3, "write_3", args::None>;

	using Out = GenericInst<OpCode::OUT, "out", args::None>;
	using CloseStream = GenericInst<OpCode::CLOSE_STREAM, "close_stream", args::None>;
	using InStr = GenericInst<OpCode::IN_STR, "in_str", args::None>;
	using InLine = GenericInst<OpCode::IN_LINE, "in_line", args::None>;
	using InBool = GenericInst<OpCode::IN_BOOL, "in_bool", args::None>;
	using InChar = GenericInst<OpCode::IN_CHAR, "in_char", args::None>;
	using InInt = GenericInst<OpCode::IN_INT, "in_int", args::None>;
	using InFloat = GenericInst<OpCode::IN_FLOAT, "in_float", args::None>;
	using InAll = GenericInst<OpCode::IN_ALL, "in_all", args::None>;
	using IsEof = GenericInst<OpCode::IS_EOF, "is_eof", args::None>;
	using IsGood = GenericInst<OpCode::IS_GOOD, "is_good", args::None>;

	using Min = GenericInst<OpCode::MIN, "min", args::None>;
	using Max = GenericInst<OpCode::MAX, "max", args::None>;
	using Round = GenericInst<OpCode::ROUND, "round", args::None>;
	using Floor = GenericInst<OpCode::FLOOR, "floor", args::None>;
	using Ceil = GenericInst<OpCode::CEIL, "ceil", args::None>;
	using Abs = GenericInst<OpCode::ABS, "abs", args::None>;
	using Hypot = GenericInst<OpCode::HYPOT, "hypot", args::None>;
	using Sqrt = GenericInst<OpCode::SQRT, "sqrt", args::None>;
	using Log = GenericInst<OpCode::LOG, "log", args::None>;
	using Ln = GenericInst<OpCode::LN, "ln", args::None>;
	using Pow = GenericInst<OpCode::POW, "pow", args::None>;
	using Sin = GenericInst<OpCode::SIN, "sin", args::None>;
	using Cos = GenericInst<OpCode::COS, "cos", args::None>;
	using Tan = GenericInst<OpCode::TAN, "tan", args::None>;

	using Bitand = GenericInst<OpCode::BITAND, "bitand", args::None>;
	using Bitor = GenericInst<OpCode::BITOR, "bitor", args::None>;
	using Bitxor = GenericInst<OpCode::BITXOR, "bitxor", args::None>;
	using Bitnot = GenericInst<OpCode::BITNOT, "bitnot", args::None>;

	using Size = GenericInst<OpCode::SIZE, "size", args::None>;
	using At = GenericInst<OpCode::AT, "at", args::None>;
	using AtWrite = GenericInst<OpCode::AT_WRITE, "at_write", args::None>;
	using Front = GenericInst<OpCode::FRONT, "front", args::None>;
	using Back = GenericInst<OpCode::BACK, "back", args::None>;

	using Insert = GenericInst<OpCode::INSERT, "insert", args::Byte>;
	using Remove = GenericInst<OpCode::REMOVE, "remove", args::Byte>;
	using Begin = GenericInst<OpCode::BEGIN, "begin", args::None>;
	using End = GenericInst<OpCode::END, "end", args::None>;
	using Push = GenericInst<OpCode::PUSH, "push", args::None>;
	using Pop = GenericInst<OpCode::POP, "pop", args::None>;
	using Peek = GenericInst<OpCode::PEEK, "peek", args::None>;
	using Contains = GenericInst<OpCode::CONTAINS, "contains", args::None>;
	using Empty = GenericInst<OpCode::EMPTY, "empty", args::None>;

	using Cast = GenericInst<OpCode::CAST, "cast", args::BytexX_0>;
	using CastBool = GenericInst<OpCode::CAST_BOOL, "cast_bool", args::None>;
	using CastChar = GenericInst<OpCode::CAST_CHAR, "cast_char", args::None>;
	using CastInt = GenericInst<OpCode::CAST_INT, "cast_int", args::None>;
	using CastFloat = GenericInst<OpCode::CAST_FLOAT, "cast_float", args::None>;
	using CastString = GenericInst<OpCode::CAST_STRING, "cast_string", args::None>;

	using TypeId = GenericInst<OpCode::TYPEID, "typeid", args::None>;
	using Clone = GenericInst<OpCode::CLONE, "clone", args::None>;

	using MemberRead = GenericInst<OpCode::MEMBER_READ, "member_read", args::Uint64>;
	using MemberWrite = GenericInst<OpCode::MEMBER_WRITE, "member_write", args::Uint64>;
	using GlobalRead = GenericInst<OpCode::GLOBAL_READ, "global_read", args::Uint64>;
	using GlobalWrite = GenericInst<OpCode::GLOBAL_WRITE, "global_write", args::Uint64>;

	class Instruction {
	public:
		template<typename T>
		Instruction(const T & i) : ptr{std::make_unique<T>(i)} {}

		template<typename T> 
		const T * as() const {
			return dynamic_cast<const T *>(ptr.get());
		}

		args::Args args() const {
			return ptr->get_args();
		}

	private:
		std::shared_ptr<InstCore> ptr;
	};
}