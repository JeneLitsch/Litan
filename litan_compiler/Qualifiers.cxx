#include "Qualifiers.hxx" 

namespace ltn::c {
	const Qualifiers Qualifiers::none {
		.is_const = false,
		.is_extern = false,
		.is_private = false,
		.is_coroutine = false,
	};



	const Qualifiers Qualifiers::just_const {
		.is_const = true,
		.is_extern = false,
		.is_private = false,
		.is_coroutine = false,
	};
}