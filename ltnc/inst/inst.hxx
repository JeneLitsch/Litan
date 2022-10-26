#pragma once
#include <variant>
#include <vector>
#include <string>
#include <cstdint>
#include "stdxx/float64_t.hxx"
#include "ltn/opcodes.hxx"

namespace ltn::c::inst {
    struct InstNone {
		constexpr inline static std::size_t size = 1;
		std::string_view name;
		OpCode opcode;
		bool operator==(const InstNone &) const = default;
	};

	struct InstUint64 {
		constexpr inline static std::size_t size = 9;
		std::string_view name;
		OpCode opcode;
		std::uint64_t value;
		bool operator==(const InstUint64 &) const = default;
	};

	struct InstUint16 {
		constexpr inline static std::size_t size = 3;
		std::string_view name;
		OpCode opcode;
		std::uint16_t value;
		bool operator==(const InstUint16 &) const = default;
	};

	struct InstJump {
		constexpr inline static std::size_t size = 9;
		std::string_view name;
		OpCode opcode;
		std::string label;
		bool operator==(const InstJump &) const = default;
	};

	struct InstTarget {
		constexpr inline static std::size_t size = 0;
		std::string_view name;
		OpCode opcode;
		std::string label;
		bool operator==(const InstTarget &) const = default;
	};

	struct InstJumpUint64 {
		constexpr inline static std::size_t size = 17;
		std::string_view name;
		OpCode opcode;
		std::string label;
		std::uint64_t value;
		bool operator==(const InstJumpUint64 &) const = default;
	};

	struct InstInt64 {
		constexpr inline static std::size_t size = 9;
		std::string_view name;
		OpCode opcode;
		std::int64_t value;
		bool operator==(const InstInt64 &) const = default;
	};

	struct InstFloat {
		constexpr inline static std::size_t size = 9;
		std::string_view name;
		OpCode opcode;
		stx::float64_t value;
		bool operator==(const InstFloat &) const = default;
	};

	struct InstByte {
		constexpr inline static std::size_t size = 2;
		std::string_view name;
		OpCode opcode;
		std::uint8_t value;	
		bool operator==(const InstByte &) const = default;
	};

	struct InstUint64Bytex {
		std::string_view name;
		OpCode opcode;
		std::vector<std::uint8_t> bytes;
		bool operator==(const InstUint64Bytex &) const = default;
	};

	struct InstBytex0 {
		std::string_view name;
		OpCode opcode;
		std::vector<std::uint8_t> bytes;
		bool operator==(const InstBytex0 &) const = default;
	};

    using Inst = std::variant<
        InstNone,
	    InstUint64,
	    InstUint16,
	    InstJump,
	    InstTarget,
	    InstJumpUint64,
	    InstInt64,
	    InstFloat,
	    InstByte,
	    InstUint64Bytex,
	    InstBytex0
    >;
    
	std::size_t inst_size(const Inst & inst);

	std::string_view name(const Inst & inst);

	OpCode opcode(const Inst & inst);

	Inst exit();
	Inst error();
	Inst state();
	Inst trY(const std::string & label);
	Inst thr0w();
	Inst build_in(std::uint16_t code);
	
	Inst add();
	Inst sub();
	Inst mlt();
	Inst div();
	Inst mod();

	Inst eql();
	Inst ueql();
	Inst lt();
	Inst gt();
	Inst lt_eql();
	Inst gt_eql();

	Inst shift_l();
	Inst shift_r();

	Inst neg();
	Inst n0t();
	Inst inc();
	Inst dec();

	Inst comp();
	Inst between();

	Inst newu(std::uint64_t u64);
	Inst newi(std::int64_t i64);
	Inst newf(stx::float64_t f64);
	Inst newc(std::uint8_t f64);
	Inst bool_true();
	Inst bool_false();
	Inst null();

	Inst newarr(std::uint64_t size);
	Inst newstr(std::vector<std::uint8_t> byte);
	Inst newout(std::uint8_t type);
	Inst newin(std::uint8_t type);
	Inst newfx(const std::string & label, std::uint64_t arity);
	Inst newclock();
	Inst newstruct();
	Inst newstack();
	Inst newqueue();
	Inst newmap();
	Inst newrng(std::uint8_t type);

	Inst jump(const std::string & label);
	Inst call(const std::string & label);
	Inst parameters(std::uint8_t byte);
	Inst retvrn();
	Inst ifelse(const std::string & label);
	
	Inst invoke();
	Inst external();
	Inst capture();

	Inst read();
	Inst write();
	Inst scrap();
	Inst duplicate();
	Inst makevar();

	Inst read_x(std::uint64_t u64);
	Inst write_x(std::uint64_t u64);
	Inst swap();

	Inst read_0();
	Inst read_1();
	Inst read_2();
	Inst read_3();

	Inst write_0();
	Inst write_1();
	Inst write_2();
	Inst write_3();

	Inst out();
	Inst close_stream();
	Inst in_str();
	Inst in_line();
	Inst in_bool();
	Inst in_char();
	Inst in_int();
	Inst in_float();
	Inst in_all();
	Inst is_eof();
	Inst is_good();

	Inst min();
	Inst max();
	Inst round();
	Inst floor();
	Inst ceil();
	Inst abs();
	Inst hypot();
	Inst sqrt();
	Inst log();
	Inst ln();
	Inst pow();
	Inst sin();
	Inst cos();
	Inst tan();

	Inst bit_and();
	Inst bit_or();
	Inst bit_xor();
	Inst bit_not();

	Inst size();
	Inst at();
	Inst at_write();
	Inst front();
	Inst back();

	Inst insert(std::uint8_t place);
	Inst remove(std::uint8_t place);
	Inst push();
	Inst pop();
	Inst peek();
	Inst contains();
	Inst empty();

	Inst cast(std::vector<std::uint8_t> code);
	Inst cast_bool();
	Inst cast_char();
	Inst cast_int();
	Inst cast_float();
	Inst cast_string();
	Inst safe_cast(std::vector<std::uint8_t> code);

	Inst type_id();
	Inst clone();

	Inst member_read(std::uint64_t id);
	Inst member_write(std::uint64_t id);
	Inst global_read(std::uint64_t id);
	Inst global_write(std::uint64_t id);
}