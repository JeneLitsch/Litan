#pragma once
inline const char * std_bits = R"###(
namespace std {
	namespace bits {
		function get(value : int, index : int) const -> bool
			=> (value << index) & 0b1 : bool
		
		function set(number : int, index : int, value : bool) const -> int
			=> (value) 
				? number | 1 << index
				: number & ~(1 << index)

	}
}
)###";