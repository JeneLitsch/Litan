#pragma once
inline const char * std_functional = R"###(
namespace std {
	function arity(id) const 
		=> build_in(fx_arity)
	
	
	
	function invoke(fx, params) 
		=> build_in(fx_invoke)
	
	
	
	function is_variadic(fx) const 
		=> build_in(fx_is_variadic)
	


	function chain(f1, f2) const
		=> lambda [f1, f2] (x) 
			=> (f2)((f1)(x))



	function is_successful(fx) {
		fx();
		return true;
	}
	except(e) {
		return false;
	}



	function noroutine() 
		=> build_in(fx_noroutine)

	function is_noroutine(cor)
		=> build_in(fx_is_noroutine)
}
)###";
