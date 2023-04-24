#pragma once
inline const char * std_iter = R"###(
	namespace std {
		build_in range(begin : int, end : int, step : int) @iter_range
		function range(begin : int, end : int) => range(begin, end, 1)
		build_in next(iterator) @iter_next
		build_in iter(iterator) @iter_iter
		namespace iter {
			build_in range(begin : int, end : int, step : int) @iter_range
			function range(begin : int, end : int) => range(begin, end, 1)
			build_in next(iterator) @iter_next
			build_in iter(iterator) @iter_iter
			build_in is_stop(value) @iter_is_stop
		}
	}
)###";
