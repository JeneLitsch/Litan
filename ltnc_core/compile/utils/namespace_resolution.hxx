#pragma once
#include "ltnc_core/ast/Ast.hxx"
namespace ltn::c::compile {
	const ast::Functional * resolve(
		const std::vector<const ast::Functional *> & functions,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name,
		const std::size_t parameters);

	const ast::Global * resolve(
		const std::vector<const ast::Global *> & globals,
		const ast::Namespace & from,
		const ast::Namespace & to,
		const std::string_view name);
}