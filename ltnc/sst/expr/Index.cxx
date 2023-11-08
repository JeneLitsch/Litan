#include "Index.hxx"
#include "ltnc/sst/bind/Binding.hxx"

namespace ltn::c::sst {
	Index::Index(expr_ptr expr, expr_ptr index)
		: expr{std::move(expr)}
		, index{std::move(index)} {}


	std::uint64_t Index::alloc() const {
		return std::max({
			this->expr->alloc(),
			this->index->alloc(),
		});
	}



	std::unique_ptr<Binding> Index::convert_to_bindung() && {
		return std::make_unique<IndexBinding>(std::move(this->expr), std::move(this->index));
	}
}