#pragma once
#include "Binding.hxx"

namespace ltn::c::sst::bind {
	struct Index final : public BindingCRTP<Index> {
		Index(expr_ptr range, expr_ptr index);
		virtual std::size_t alloc_count() const override;
		virtual ~Index();

		expr_ptr range;
		expr_ptr index;
	};



	std::unique_ptr<Index> index(expr_ptr range, expr_ptr index);
}
