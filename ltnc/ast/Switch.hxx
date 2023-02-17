#pragma once
#include <vector>
#include "stdxx/memory.hxx"
#include "ltnc/SourceLocation.hxx"

namespace ltn::c::ast {
	struct Expression;

	template<typename Base>
	struct Switch : Base {
		Switch(const SourceLocation & location) : Base(location) {}
		std::unique_ptr<Expression> condition;
		std::vector<std::pair<
			std::unique_ptr<Expression>,
			std::unique_ptr<Base>
		>> cases;
		std::unique_ptr<Base> d3fault;
	};
}