#pragma once
inline const char * std_algorithm = R"###(
namespace std {
	function for_each(array, fx) {
		for (elem : array) fx(elem);
	}



	function sum(iter, start) => std::reduce_l(iter, lambda(a, b) => a + b, start)
	function sum(range) => sum(range, 0)



	build_in sort_ascn(range)
		@ algorithm_sort_ascn
	


	build_in sort_desc(range)
		@ algorithm_sort_desc
	


	build_in is_sorted_ascn(range) const
		@ algorithm_is_sorted_ascn
	


	build_in is_sorted_desc(range) const 
		@ algorithm_is_sorted_desc
	


	build_in find(range, key) const
		@ algorithm_find
	


	build_in fill(range, target)
		@ algorithm_fill
	


	build_in reverse(range)
		@ algorithm_reverse



	function transform(in, fx) {
		var out = [];
		for(e : in) std::insert_back(out, fx(e));
		return out;
	} 


	function zip(ranges...)
		=> transform(std::zipped_impl(ranges), lambda(x) => x)



	build_in reduce_l(iter, fx, init) @algorithm_reduce_l_3
	build_in reduce_l(iter, fx) @algorithm_reduce_l_2

	function reduce_r(iter, fx, init) => std::reduce_l(std::reversed(iter), fx, init)
	function reduce_r(iter, fx) => std::reduce_l(std::reversed(iter), fx)
}
)###";