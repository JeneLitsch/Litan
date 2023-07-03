#pragma once
inline const char * std_algorithm = R"###(
namespace std {
	function for_each(array, fx) {
		for (elem : array) fx(elem);
	}



	function sum(iter, start) 
		=> std::reduce_l(iter, lambda(a, b) => a + b, start)
	


	function sum(range) 
		=> sum(range, 0)



	function sort_ascn(range)
		=> build_in(algorithm_sort_ascn)
	


	function sort_desc(range)
		=> build_in(algorithm_sort_desc)



	function is_sorted_ascn(range) const
		=> build_in(algorithm_is_sorted_ascn)
	


	function is_sorted_desc(range) const 
		=> build_in(algorithm_is_sorted_desc)
	


	function find(range, key) const
		=> build_in(algorithm_find)
	


	function fill(range, target)
		=> build_in(algorithm_fill)
	


	function reverse(range)
		=> build_in(algorithm_reverse)



	function transform(in, fx) {
		var out = [];
		for(e : in) std::insert_back(out, fx(e));
		return out;
	} 



	function zip(ranges...)
		=> transform(std::zipped_impl(ranges), lambda(x) => x)



	function reduce_l(iter, fx, init) const 
		=> build_in(algorithm_reduce_l_3)
	
	
	
	function reduce_l(iter, fx) const
		=> build_in(algorithm_reduce_l_2)



	function reduce_r(iter, fx, init) const 
		=> std::reduce_l(std::reversed(iter), fx, init)
	
	
	
	function reduce_r(iter, fx) const
		=> std::reduce_l(std::reversed(iter), fx)
}
)###";