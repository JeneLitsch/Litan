#pragma once
inline const char * std_math = R"###(
namespace std {
	build_in min(a, b) const
		@ math_min
	


	build_in max(a, b) const
		@ math_max
	


	build_in clamp(x, min, max) const
		@ math_clamp



	build_in round(a) const
		@ math_round



	build_in floor(b) const
		@ math_floor



	build_in ceil(b) const
		@ math_ceil



	build_in abs(b) const
		@ math_abs



	build_in hypot(a, b) const
		@ math_hypot



	build_in sqrt(a) const
		@ math_sqrt



	function cbrt(a) const 
		=> a ** (1.0/3.0) 
	


	build_in log(x, b) const
		@ math_log



	build_in ld(x) const
		@ math_ld



	build_in lg(x) const
		@ math_lg



	build_in ln(x) const
		@ math_ln



	build_in pow(b, e) const
		@ math_pow



	build_in sin(b) const
		@ math_sin



	build_in cos(b) const
		@ math_cos



	build_in tan(b) const
		@ math_tan



	function lerp(a, b, t) const 
		=> a + t * (b-a)



	function is_between(value, min, max) const
		=> value >= min && value <= max



	define pi  = 3.14159265359; 
	define e   = 2.71828182846;
	define tau = 6.28318530718;


	namespace num {
		define pi = 3.14159265359; 
	}
}
)###";
