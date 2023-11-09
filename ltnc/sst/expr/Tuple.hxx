#pragma once
#include <vector>
#include "Literal.hxx"

namespace ltn::c::sst::expr {
	struct Tuple final: public Literal {
		Tuple();

		virtual std::uint64_t alloc() const override;
		virtual void accept(const ExprVisitor & visitor) const override;
		void push_back(expr_ptr elem);

		std::vector<expr_ptr> elements;
	};

	std::unique_ptr<Tuple> tuple();
}