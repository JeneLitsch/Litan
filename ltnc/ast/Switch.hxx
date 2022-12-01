#pragma once
#include <vector>
#include "stdxx/memory.hxx"

namespace ltn::c::ast {
	struct Expression;

	template<typename Base, typename Case>
	struct Switch : Base {
		Switch(const SourceLocation & location) : Base(location) {}
		std::unique_ptr<Expression> condition;
		std::vector<std::pair<
			std::unique_ptr<Expression>,
			std::unique_ptr<Case>
		>> cases;
		std::unique_ptr<Case> d3fault;
	};
}