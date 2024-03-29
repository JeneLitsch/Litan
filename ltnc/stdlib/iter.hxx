#pragma once
inline const char * std_iter = R"###(
	namespace std {
		function range(begin, end, step) const => build_in(iter_range)
		function range(begin, end) const => range(begin, end, 1)
		function zipped(iters...) const => zipped_impl(iters)
		function reversed(iters) const => build_in(iter_reversed)
		
		namespace iter {
			function range(begin, end, step) const => build_in(iter_range)
			function range(begin, end) const => range(begin, end, 1)
			function zipped(iters...) const => zipped_impl(iters)
			function reversed(iters) const => build_in(iter_reversed)

			function next(iterator) => build_in(iter_next)
			function get(iterator) const => build_in(iter_get)
			function move(iterator, steps) => build_in(iter_move)
			function iter(iterator) const => build_in(iter_iter)
			function is_stop(value) const => build_in(iter_is_stop)
		}

		function zipped_impl(iters) const private => build_in(iter_zipped) 
	}
)###";
