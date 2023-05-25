#pragma once
inline const char * std_functional = R"###(
namespace std {
	build_in arity(id) const @fx_arity

	build_in invoke(fx, params) @fx_invoke
	
	build_in is_variadic(fx) const @fx_is_variadic
	
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
}
)###";
