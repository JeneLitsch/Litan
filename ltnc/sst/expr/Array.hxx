#pragma once
#include <vector>
#include "Literal.hxx"

namespace ltn::c::sst {
	struct Array final: public Literal {
		Array();

		virtual std::uint64_t alloc() const override;
		virtual void accept(const ExprVisitor & visitor) const override;
		void push_back(expr_ptr elem);

		std::vector<expr_ptr> elements;
	};

	std::unique_ptr<Array> array();
}