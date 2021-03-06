#pragma once
inline const char * std_algorithm = R"###(
namespace std {
	// executes "fx" for each element in range
	function for_each(range, fx) {
		for (i : std::begin(range) -> std::end(range)) {
			std::invoke(fx, [std::array(range)[i]]);
		}
	}

	// starts at "start" and adds (+=) all elements in range
	function sum(range, start) {
		var value = start;
		for (i : std::begin(range) -> std::end(range)) {
			value += std::array(range)[i];
		}
		return value;
	}


	// starts at 0 and adds (+=) all elements in range
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