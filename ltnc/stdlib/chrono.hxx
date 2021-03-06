#pragma once
inline const char * std_chrono = R"###(
namespace std {
	namespace chrono {
		build_in clock()                @ chrono_clock
		build_in to_seconds(clock)      @ chrono_to_seconds
		build_in to_milliseconds(clock) @ chrono_to_milliseconds

		function wait(seconds) {
			var clock = clock();
			return wait(seconds, clock);
		}

		function wait(seconds, clock) {
			var start = to_seconds(clock);
			var current = start;
			while(current - start <= seconds) {
				current = to_seconds(clock);
			}
		}
	}
}
)###";
