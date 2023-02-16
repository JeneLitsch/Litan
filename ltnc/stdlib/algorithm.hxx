#pragma once
inline const char * std_algorithm = R"###(
namespace std {
	function for_each(array, fx) {
		for (elem : array) fx(elem);
	}

	function sum(array, start) {
		var value = start;
		for (i : 0 -> std::size(array)) {
			value = value + array[i];
		}
		return value;
	}


	function sum(range) => sum(range, 0)

	build_in sort_ascn(range)            @ algorithm_sort_ascn
	build_in sort_desc(range)            @ algorithm_sort_desc
	build_in is_sorted_ascn(range) const @ algorithm_is_sorted_ascn
	build_in is_sorted_desc(range) const @ algorithm_is_sorted_desc
	build_in find(range, key) const      @ algorithm_find
	build_in copy_front(range, key)      @ algorithm_copy_front
	build_in copy_back(range, key)       @ algorithm_copy_back
	build_in fill(range, target)         @ algorithm_fill
	build_in reverse(range)              @ algorithm_reverse
}
)###";