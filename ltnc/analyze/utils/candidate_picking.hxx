#pragma once
#include "ltnc/type/check.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	const ast::Functional * pick_candidate_exact(
		const std::vector<const ast::Functional *> & candidates,
		const std::vector<type::Type> & arguments);

	const ast::Functional * pick_candidate(
		const std::vector<const ast::Functional *> & candidates,
		const std::vector<type::Type> & arguments);

	const sst::Definition * pick_candidate(
		const std::vector<const sst::Definition *> & candidates);

	const sst::Global * pick_candidate(
		const std::vector<const sst::Global *> & candidates);

	const ast::FunctionTemplate * pick_candidate(
		const std::vector<const ast::FunctionTemplate *> & candidates);
}