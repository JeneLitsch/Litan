#include "Index.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::bind {
	Index::Index(expr_ptr range, expr_ptr index)
		: range{std::move(range)}
		, index{std::move(index)} {}



	std::size_t Index::alloc_count() const { 
		return 0;
	}



	Index::~Index() {}



	std::unique_ptr<Index> index(expr_ptr range, expr_ptr index) {
		return std::make_unique<Index>(std::move(range), std::move(index));
	}
}
