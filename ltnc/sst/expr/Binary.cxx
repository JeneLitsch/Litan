#include "Binary.hxx"
#include <algorithm>

namespace ltn::c::sst::expr {
	Binary::Binary(Op op, expr_ptr l, expr_ptr r)
		: op(op)
		, l(std::move(l))
		, r(std::move(r)) {}



	std::uint64_t Binary::alloc() const {
		return std::max({l->alloc(), r->alloc()});
	}



	std::unique_ptr<Binary> binary(Binary::Op op, expr_ptr l, expr_ptr r) {
		return std::make_unique<Binary>(op, std::move(l), std::move(r));
	}
}