#include "Binary.hxx"

namespace ltn::c::sst {
	Binary::Binary(Op op, expr_ptr l, expr_ptr r)
		: op(op)
		, l(std::move(l))
		, r(std::move(r)) {}



	std::uint64_t Binary::alloc() const {
		return std::max({l->alloc(), r->alloc()});
	}
}