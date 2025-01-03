#include "Index.hxx"
#include "litan_compiler/sst/bind/Index.hxx"
#include <algorithm>

namespace ltn::c::sst::expr {
	Index::Index(expr_ptr expr, expr_ptr index)
		: expr {std::move(expr)}
		, index{std::move(index)} {}


	std::uint64_t Index::alloc() const {
		return std::max({
			this->expr->alloc(),
			this->index->alloc(),
		});
	}



	bind_ptr Index::convert_to_bindung() && {
		return bind::index(std::move(this->expr), std::move(this->index));
	}



	std::unique_ptr<Index> index(expr_ptr expr, expr_ptr index) {
		return std::make_unique<Index>(std::move(expr), std::move(index));
	}
}