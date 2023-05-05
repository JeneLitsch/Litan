#pragma once
inline const char * std_bits = R"###(
namespace std {
	namespace bits {
		function get(value, index) const => ((value << index) & 0b1) == 1
		
		function set(number, index, value) const
			=> (value) 
				? number | 1 << index
				: number & ~(1 << index)

	}
}
)###";