#pragma once
inline const char * std_lib = R"###(
namespace std {
	namespace lib {
		build_in open(path : string)
			-> any
			@ lib_open
		
		build_in close(library : any)
			-> null
			@ lib_close
		
		build_in get_fx(library, fx_name : string)
			-> any
			@ lib_get_fx
	}
}
)###";
