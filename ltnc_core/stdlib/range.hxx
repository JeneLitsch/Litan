#pragma once
inline const char * std_range = R"###(
namespace std {
	function whole(array) const {
		return range(array, 0, std::size(array));
	}


	function first_n(array, n) const {
		return range(array, 0, n);
	}


	function last_n(array, n) const {
		var size = std::size(array);
		return range(array, size - n, size);
	}


	build_in range(array, begin, end) const @ range
}
)###";
