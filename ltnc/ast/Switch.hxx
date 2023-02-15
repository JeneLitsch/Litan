#pragma once
#include <vector>
#include "stdxx/memory.hxx"

namespace ltn::c::ast {
	struct ExprBase;

	template<typename Base>
	struct Switch : Base {
		Switch(const SourceLocation & location) : Base(location) {}
		std::unique_ptr<ExprBase> condition;
		std::vector<std::pair<
			std::unique_ptr<ExprBase>,
			std::unique_ptr<Base>
		>> cases;
		std::unique_ptr<Base> d3fault;
	};
}