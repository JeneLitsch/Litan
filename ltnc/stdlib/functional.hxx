#pragma once
inline const char * std_functional = R"###(
namespace std {
	build_in arity(id) const @functional_arity

	build_in invoke(fx, params) @functional_invoke_2
	
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
