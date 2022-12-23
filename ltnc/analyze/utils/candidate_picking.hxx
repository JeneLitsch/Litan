#pragma once
#include "ltnc/type/check.hxx"
#include "ltnc/ast/AST.hxx"

namespace ltn::c {
	template<typename DeclNode>
	const DeclNode * pick_candidate(
		const std::vector<const DeclNode *> & candidates) {
		
		if(candidates.size() == 1) return candidates[0];
		else return nullptr;
	}



	const ast::Functional * pick_candidate(
		const std::vector<const ast::Functional *> & candidates,
		const std::vector<type::Type> & arguments);
}