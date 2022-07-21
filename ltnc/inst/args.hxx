#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include "stdxx/float64_t.hxx"

namespace ltn::inst::args {
	struct None {
		constexpr inline static std::size_t size = 1;

		bool operator==(const None &) const = default;
	};

	struct Uint64 {
		Uint64() : Uint64{0} {}
		Uint64(auto v) : value{static_cast<std::uint64_t>(v)} {}
		constexpr inline static std::size_t size = 9;
		std::uint64_t value;

		bool operator==(const Uint64 &) const = default;
	};

	struct Uint16 {
		Uint16() : Uint16{0} {}
		Uint16(auto v) : value{static_cast<std::uint16_t>(v)} {}
		constexpr inline static std::size_t size = 3;
		std::uint16_t value;
	};

	struct Jump {
		constexpr inline static std::size_t size = 9;
		std::string name;

		bool operator==(const Jump &) const = default;
	};

	struct Target {
		constexpr inline static std::size_t size = 0;
		std::string name;

		bool operator==(const Target &) const = default;
	};

	struct Jump_Uint64 {
		constexpr inline static std::size_t size = 17;
		std::string name;
		std::uint64_t value;

		bool operator==(const Jump_Uint64 &) const = default;
	};

	struct Int64 {
		constexpr inline static std::size_t size = 9;
		std::int64_t value;

		bool operator==(const Int64 &) const = default;
	};

	struct Float {
		constexpr inline static std::size_t size = 9;
		stx::float64_t value;
		
		bool operator==(const Float &) const = default;
	};

	struct Byte {
		Byte() : Byte{0} {}
		Byte(auto v) : value{static_cast<std::uint8_t>(v)} {}
		constexpr inline static std::size_t size = 2;
		std::uint8_t value;
	
		bool operator==(const Byte &) const = default;
	};

	struct Uint64_BytexX {
		std::vector<std::uint8_t> bytes;

		bool operator==(const Uint64_BytexX &) const = default;
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
		return 9 + args.bytes.size();
	}
}