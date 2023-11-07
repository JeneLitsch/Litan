#include "FxPointer.hxx"
#include "Var.hxx"

namespace ltn::c::sst {
	FxPointer::FxPointer(
		const Label & label,
		std::size_t arity,
		bool is_variadic)
		: label{label}
		, arity{arity}
		, is_variadic{is_variadic} {}



	std::uint64_t FxPointer::alloc() const {
		return 0;
	}



	FxPointer::~FxPointer() {}
}