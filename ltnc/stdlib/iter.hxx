#pragma once
inline const char * std_iter = R"###(
	namespace std {
		build_in range(begin, end, step) const @iter_range
		function range(begin, end) const => range(begin, end, 1)
		build_in combined(iters) @iter_combined 
		namespace iter {
			build_in range(begin, end, step) const @iter_range
			function range(begin, end) const => range(begin, end, 1)
			build_in next(iterator) @iter_next
			build_in get(iterator) @iter_get
			build_in move(iterator, steps) @iter_move
			build_in iter(iterator) const @iter_iter
			build_in is_stop(value) const @iter_is_stop
			build_in combined(iters) @iter_combined 
		}
	}
)###";
