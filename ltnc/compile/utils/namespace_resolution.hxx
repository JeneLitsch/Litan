#pragma once
#include "ltnc/ast/Ast.hxx"
namespace ltn::c {
	const ast::Functional * resolve(
		const std::vector<const ast::Functional *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t parameters);

	const ast::Definition * resolve(
		const std::vector<const ast::Definition *> & definitions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);

	const ast::Global * resolve(
		const std::vector<const ast::Global *> & globals,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);

	const ast::FunctionTemplate * resolve(
		const std::vector<const ast::FunctionTemplate *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t function_parameters,
		const std::size_t template_parameters);
}