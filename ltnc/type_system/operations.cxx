#include "operations.hxx"

namespace ltn::c::type {
	const BinaryOperation arithmetic = {
		.signatures = {
			from<Integer,  Integer>  ::unidirect ::to<Integer>,
			from<Floating, Integer>  ::birect    ::to<Floating>,
			from<Floating, Floating> ::unidirect ::to<Floating>,
		}
	};
}