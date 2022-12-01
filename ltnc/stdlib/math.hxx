#pragma once
inline const char * std_math = R"###(
namespace std {
	build_in min(a, b) const
		@ math_min
	


	build_in max(a, b) const
		@ math_max
	


	build_in clamp(x, min, max) const
		@ math_clamp



	build_in round(a:float) const -> int
		@ math_round



	build_in floor(b:float) const -> int
		@ math_floor



	build_in ceil(b:float) const -> int
		@ math_ceil



	build_in abs(b) const
		@ math_abs



	build_in hypot(a:float, b:float) const -> float
		@ math_hypot



	build_in sqrt(a:float) const -> float
		@ math_sqrt



	function cbrt(a:float) const -> float 
		=> a ** (1.0/3.0) 
	


	build_in log(x:float, b:float) const -> float
		@ math_log



	build_in ld(x:float) const -> float
		@ math_ld



	build_in lg(x:float) const -> float
		@ math_lg



	build_in ln(x:float) const -> float
		@ math_ln



	function pow(b, e) const => b**e



	build_in sin(b:float) const -> float
		@ math_sin



	build_in cos(b:float) const -> float
		@ math_cos



	build_in tan(b:float) const -> float
		@ math_tan



	function lerp(a:float, b:float, t:float) const -> float 
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
