#pragma once
inline const char * std_chrono = R"###(
namespace std {
	namespace chrono {
		function clock()                
			=> build_in(chrono_clock)


			
		function to_seconds(clock)      
			=> build_in(chrono_to_seconds)


			
		function to_milliseconds(clock) 
			=> build_in(chrono_to_milliseconds)

			

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
