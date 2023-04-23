#pragma once
inline const char * std_iter = R"###(
	namespace std {
		build_in range(begin : int, end : int, step : int) @iter_range
		build_in next(iterator) @iter_next
	}
)###";
