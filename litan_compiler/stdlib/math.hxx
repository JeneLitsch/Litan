#pragma once
inline const char * std_math = R"###(
namespace std {
	function min(a, b) const
		=> build_in(math_min)
	


	function max(a, b) const
		=> build_in(math_max)
	


	function clamp(x, min, max) const
		=> build_in(math_clamp)



	function round(a) const
		=> build_in(math_round)



	function floor(b) const
		=> build_in(math_floor)



	function ceil(b) const
		=> build_in(math_ceil)



	function abs(b) const
		=> build_in(math_abs)



	function hypot(a, b) const
		=> build_in(math_hypot)



	function sqrt(a) const
		=> build_in(math_sqrt)



	function cbrt(a) const 
		=> a ** (1.0/3.0) 
	


	function log(x, b) const
		=> build_in(math_log)



	function ld(x) const
		=> build_in(math_ld)



	function lg(x) const
		=> build_in(math_lg)



	function ln(x) const
		=> build_in(math_ln)



	function pow(b, e) const => b**e



	function sin(b) const 
		=> build_in(math_sin)



	function cos(b) const
		=> build_in(math_cos)



	function tan(b) const
		=> build_in(math_tan)



	function lerp(a, b, t) const 
		=> a + t * (b-a)



	function is_between(value, min, max) const
		=> value >= min && value <= max



	def pi  = 3.14159265359; 
	def e   = 2.71828182846;
	def tau = 6.28318530718;


	namespace num {
		def pi = 3.14159265359; 
	}
}
)###";
