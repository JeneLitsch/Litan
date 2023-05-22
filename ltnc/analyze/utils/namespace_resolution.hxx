#pragma once
#include "ltnc/sst/SST.hxx"
#include "ltnc/ast/AST.hxx"
namespace ltn::c {
	enum class VariadicMode { REQUIRED, ALLOWED, PROHIBITED };
	
	const ast::Functional * resolve(
		const std::vector<const ast::Functional *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t parameters,
		VariadicMode variadic_mode);

	const sst::Definition * resolve(
		const std::vector<const sst::Definition *> & definitions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);

	const sst::Global * resolve(
		const std::vector<const sst::Global *> & globals,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);
}