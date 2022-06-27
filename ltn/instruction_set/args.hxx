#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include "stdxx/float64_t.hxx"

namespace ltn::inst::args {
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

	using Args = std::variant<
		args::None,
		args::Uint64,
		args::Uint16,
		args::Jump,
		args::Target,
		args::Jump_Uint64,
		args::Int64,
		args::Float,
		args::Byte,
		args::Uint64_BytexX>;

	inline std::size_t size(const auto & args) {
		return args.size;
	}

	inline std::size_t size(const Uint64_BytexX & args) {
		return 9 + args.value;
	}
}