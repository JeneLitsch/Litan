#pragma once
inline const char * std_random = R"###(
namespace std {
	namespace random {
		build_in mersenne()
			@ random_mersenne_0
		
		build_in mersenne(seed) const
			@ random_mersenne_1
		
		build_in rand(rng) -> int
			@ random_rand
		
		build_in rand_int(rng, min, max) -> int  
			@ random_rand_int
		
		build_in rand_float(rng, min, max) -> float
			@ random_rand_float
		
		build_in split(rng)
			@ random_split

		function decision(rng, p) -> bool
			=> rand_float(rng, 0, 1) < p

		function rand_element(rng, range)
			=> range[rand_int(rng, 0, size(range) - 1)]
	}
}
)###";
