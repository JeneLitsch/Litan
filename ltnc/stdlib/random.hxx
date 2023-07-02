#pragma once
inline const char * std_random = R"###(
namespace std {
	namespace random {
		function mersenne()
			=> build_in(random_mersenne_0)
		
		function mersenne(seed) const
			=> build_in(random_mersenne_1)
		
		function rand(rng)
			=> build_in(random_rand)
		
		function rand_int(rng, min, max)   
			=> build_in(random_rand_int)
		
		function rand_float(rng, min, max) 
			=> build_in(random_rand_float)
		
		function split(rng)
			=> build_in(random_split)

		function decision(rng, p) 
			=> rand_float(rng, 0, 1) < p

		function rand_element(rng, range)
			=> range[rand_int(rng, 0, size(range) - 1)]
	}
}
)###";
