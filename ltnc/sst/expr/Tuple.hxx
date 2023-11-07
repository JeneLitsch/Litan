#pragma once
#include <vector>
#include "Literal.hxx"

namespace ltn::c::sst {
	struct Tuple final: public Literal {
		Tuple();

		virtual std::uint64_t alloc() const override;

		virtual void accept(const ExprVisitor & visitor) const override;

		std::vector<expr_ptr> elements;
	};
}