#pragma once
inline const char * std_iter = R"###(
	namespace std {
		build_in range(begin : int, end : int, step : int) const @iter_range
		function range(begin : int, end : int) const => range(begin, end, 1)
		namespace iter {
			build_in range(begin : int, end : int, step : int) const @iter_range
			function range(begin : int, end : int) const => range(begin, end, 1)
			build_in next(iterator) @iter_next
			build_in iter(iterator) const @iter_iter
			build_in is_stop(value) const -> bool @iter_is_stop
		}
	}
)###";
