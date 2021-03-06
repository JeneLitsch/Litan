#pragma once
inline const char * std_functional = R"###(
namespace std {
	build_in arity(id)            @ functional_arity

	build_in external(id)         @ functional_external
	
	build_in invoke(fx, params)   @ functional_invoke_2
	build_in invoke(fx)           @ functional_invoke_1
	
	build_in invoke_0(f)          @ functional_invoke_1
	function invoke_1(f, a)       => invoke(f, [a])
	function invoke_2(f, a, b)    => invoke(f, [a,b])
	function invoke_3(f, a, b, c) => invoke(f, [a,b,c])

	function chain(f1, f2)
		=> lambda [f1, f2] (x) 
			=> (f2)((f1)(x))
}
)###";
