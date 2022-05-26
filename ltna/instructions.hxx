#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include "ltn/float64_t.hxx"
#include "ltn/InstructionSet.hxx"

namespace ltn::a::inst {
	namespace args {
		struct None {
			constexpr inline static std::size_t size = 1;
		};

		struct Uint64 {
			constexpr inline static std::size_t size = 9;
			std::uint64_t value;
		};

		struct Uint16 {
			constexpr inline static std::size_t size = 3;
			std::uint16_t value;
		};

		struct Jump {
			constexpr inline static std::size_t size = 9;
			std::string name;
		};

		struct Target {
			constexpr inline static std::size_t size = 0;
			std::string name;
		};

		struct Jump_Uint64 {
			constexpr inline static std::size_t size = 17;
			std::string name;
			std::uint64_t value;
		};

		struct Int64 {
			constexpr inline static std::size_t size = 9;
			std::int64_t value;
		};

		struct Float {
			constexpr inline static std::size_t size = 9;
			stx::float64_t value;
		};

		struct Byte {
			constexpr inline static std::size_t size = 2;
			std::uint8_t value;
		};

		struct Uint64_BytexX {
			std::uint64_t value;
			std::vector<std::uint8_t> bytes;
		};

		inline std::size_t size(const auto & args) {
			return args.size;
		}

		inline std::size_t size(const Uint64_BytexX & args) {
			return 9 + args.value;
		}
	}

	template<Inst OPCODE, typename Args = args::None>
	struct Base {
		inline constexpr static auto opcode = OPCODE;
		Args args;
	};

	struct Label {
		args::Target args;
	};

	struct Exit    : Base<Inst::EXIT> {};
	struct Error   : Base<Inst::ERROR> {};
	struct State   : Base<Inst::STATE> {};
	struct Try     : Base<Inst::TRY, args::Jump> {};
	struct Throw   : Base<Inst::THROW> {};
	struct BuildIn : Base<Inst::BUILD_IN, args::Uint16> {};
	
	struct Add     : Base<Inst::ADD> {};
	struct Sub     : Base<Inst::SUB> {};
	struct Mlt     : Base<Inst::MLT> {};
	struct Div     : Base<Inst::DIV> {};
	struct Mod     : Base<Inst::MOD> {};
	
	struct Eql     : Base<Inst::EQL> {};
	struct Ueql    : Base<Inst::UEQL> {};
	struct Sml     : Base<Inst::SML> {};
	struct Bgr     : Base<Inst::BGR> {};
	struct Smleql  : Base<Inst::SMLEQL> {};
	struct Bgreql  : Base<Inst::BGREQL> {};

	struct ShiftL  : Base<Inst::SHIFT_L> {};
	struct ShiftR  : Base<Inst::SHIFT_R> {};

	struct Neg     : Base<Inst::NEG> {};
	struct Not     : Base<Inst::NOT> {};
	struct Inc     : Base<Inst::INC> {};
	struct Dec     : Base<Inst::DEC> {};
	
	struct Comp    : Base<Inst::COMP> {};
	struct Approx  : Base<Inst::APPROX> {};
	struct Between : Base<Inst::BETWEEN> {};

	struct Newu    : Base<Inst::NEWU, args::Uint64> {};
	struct Newi    : Base<Inst::NEWI, args::Int64> {};
	struct Newf    : Base<Inst::NEWF, args::Float> {};
	struct Newc    : Base<Inst::NEWC, args::Byte> {};
	struct True    : Base<Inst::TRUE> {};
	struct False   : Base<Inst::FALSE> {};
	struct Null    : Base<Inst::NVLL> {};

	struct Newarr  : Base<Inst::NEWARR, args::Uint64> {};
	struct Newstr  : Base<Inst::NEWSTR, args::Uint64_BytexX> {};
	struct Newout  : Base<Inst::NEWOUT, args::Byte> {};
	struct Newin   : Base<Inst::NEWIN,  args::Byte> {};
	struct Newfx   : Base<Inst::NEWFX,  args::Jump_Uint64> {};
	struct Newclock: Base<Inst::NEWCLOCK> {};
	struct Newstruct: Base<Inst::NEWSTRUCT> {};
	struct Newrange: Base<Inst::NEWRANGE> {};
	struct Newstack: Base<Inst::NEWSTACK> {};
	struct Newqueue: Base<Inst::NEWQUEUE> {};
	struct Newmap  : Base<Inst::NEWMAP> {};
	struct Newrng  : Base<Inst::NEWRNG, args::Byte> {};

	struct Jump    : Base<Inst::JUMP, args::Jump> {};
	struct Call    : Base<Inst::CALL, args::Jump> {};
	struct Params  : Base<Inst::PARAMETERS, args::Byte> {};
	struct Return  : Base<Inst::RETURN> {};
	struct Ifelse  : Base<Inst::IF, args::Jump> {};
	
	struct Invoke  : Base<Inst::INVOKE> {};
	struct External: Base<Inst::EXTERNAL> {};
	struct Capture : Base<Inst::CAPTURE> {};
	
	struct Read    : Base<Inst::READ> {};
	struct Write   : Base<Inst::WRITE> {};
	struct Scrap   : Base<Inst::SCRAP> {};
	struct Duplicate: Base<Inst::DUPLICATE> {};
	struct Makevar : Base<Inst::MAKEVAR> {};
	struct Readx   : Base<Inst::READ_X, args::Uint64> {};
	struct Writex  : Base<Inst::WRITE_X, args::Uint64> {};
	struct Swap    : Base<Inst::SWAP> {};

	struct Read0   : Base<Inst::READ_0> {};
	struct Read1   : Base<Inst::READ_1> {};
	struct Read2   : Base<Inst::READ_2> {};
	struct Read3   : Base<Inst::READ_3> {};

	struct Write0  : Base<Inst::WRITE_0> {};
	struct Write1  : Base<Inst::WRITE_1> {};
	struct Write2  : Base<Inst::WRITE_2> {};
	struct Write3  : Base<Inst::WRITE_3> {};

	struct Out     : Base<Inst::OUT> {};
	struct Stylize : Base<Inst::STYLIZE, args::Byte> {};
	struct CloseStream : Base<Inst::CLOSE_STREAM, args::Byte> {};
	struct InStr   : Base<Inst::IN_STR> {};
	struct InLine  : Base<Inst::IN_LINE> {};
	struct InBool  : Base<Inst::IN_BOOL> {};
	struct InChar  : Base<Inst::IN_CHAR> {};
	struct InInt   : Base<Inst::IN_INT> {};
	struct InFloat : Base<Inst::IN_FLOAT> {};
	struct InAll   : Base<Inst::IN_ALL> {};
	struct IsEof   : Base<Inst::IS_EOF> {};
	struct IsGood  : Base<Inst::IS_GOOD> {};

	struct Min     : Base<Inst::MIN> {};
	struct Max     : Base<Inst::MAX> {};
	struct Round   : Base<Inst::ROUND> {};
	struct Floor   : Base<Inst::FLOOR> {};
	struct Ceil    : Base<Inst::CEIL> {};
	struct Abs     : Base<Inst::ABS> {};
	struct Hypot   : Base<Inst::HYPOT> {};
	struct Sqrt    : Base<Inst::SQRT> {};
	struct Log     : Base<Inst::LOG> {};
	struct Ln      : Base<Inst::LN> {};
	struct Pow     : Base<Inst::POW> {};

	struct Sin     : Base<Inst::SIN> {};
	struct Cos     : Base<Inst::COS> {};
	struct Tan     : Base<Inst::TAN> {};

	struct Bitand  : Base<Inst::BITAND> {};
	struct Bitor   : Base<Inst::BITOR> {};
	struct Bitxor  : Base<Inst::BITXOR> {};
	struct Bitnot  : Base<Inst::BITNOT> {};

	struct Size    : Base<Inst::SIZE> {};
	struct At      : Base<Inst::AT> {};
	struct AtWrite : Base<Inst::AT_WRITE> {};
	struct Front   : Base<Inst::FRONT> {};
	struct Back    : Base<Inst::BACK> {};
	struct Insert  : Base<Inst::INSERT, args::Byte> {};
	struct Remove  : Base<Inst::REMOVE, args::Byte> {};
	struct Begin   : Base<Inst::BEGIN> {};
	struct End     : Base<Inst::END> {};
	struct Push    : Base<Inst::PUSH> {};
	struct Pop     : Base<Inst::POP> {};
	struct Peek    : Base<Inst::PEEK> {};
	struct Contains: Base<Inst::CONTAINS> {};
	
	struct CastBool   : Base<Inst::CAST_BOOL> {};
	struct CastChar   : Base<Inst::CAST_CHAR> {};
	struct CastInt    : Base<Inst::CAST_INT> {};
	struct CastFloat  : Base<Inst::CAST_FLOAT> {};
	struct CastString : Base<Inst::CAST_STRING> {};
	struct CastArray  : Base<Inst::CAST_ARRAY> {};

	struct TypeId     : Base<Inst::TYPEID> {};
	struct Clone      : Base<Inst::CLONE> {};
	
	struct MemberRead  : Base<Inst::MEMBER_READ, args::Uint64> {};
	struct MemberWrite : Base<Inst::MEMBER_WRITE, args::Uint64> {};

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