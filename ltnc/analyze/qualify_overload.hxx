#pragma once
#include "ltnc/ast/AST.hxx"
#include "utils/Context.hxx"
#include "utils/Scope.hxx"

namespace ltn::c {
	const ast::Functional * qualify_overload(
		const ast::Overload & overload,
		const FunctionTable & fx_table,
		const std::vector<sst::expr_ptr> & arguments,
		const Scope & scope);
}