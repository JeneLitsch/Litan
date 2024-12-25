#pragma once
#include <cstdint>

namespace ltn::type_code {
	inline constexpr std::uint8_t ANY           = 'x';
	inline constexpr std::uint8_t NVLL          = 'N';
	inline constexpr std::uint8_t BOOL          = 'b';
	inline constexpr std::uint8_t INT           = 'i';
	inline constexpr std::uint8_t FLOAT         = 'f';
	inline constexpr std::uint8_t ARRAY         = 'a';
	inline constexpr std::uint8_t TUPLE         = 't';
	inline constexpr std::uint8_t TUPLE_N       = 'T';
	inline constexpr std::uint8_t STRING        = 's';
	inline constexpr std::uint8_t ISTREAM       = '>';
	inline constexpr std::uint8_t OSTREAM       = '<';
	inline constexpr std::uint8_t FX            = 'F';
	inline constexpr std::uint8_t FX_N          = 'X';
	inline constexpr std::uint8_t COROUTINE     = 'C';
	inline constexpr std::uint8_t ITERATOR      = 'I';
	inline constexpr std::uint8_t ITERATOR_STOP = '|';
	inline constexpr std::uint8_t RNG           = '?';
	inline constexpr std::uint8_t TYPE          = ':';
	inline constexpr std::uint8_t CLOCK         = 'H';
	inline constexpr std::uint8_t STACK         = 'S';
	inline constexpr std::uint8_t QUEUE         = 'Q';
	inline constexpr std::uint8_t MAP           = 'M';
	inline constexpr std::uint8_t STRUCT        = '.';
}