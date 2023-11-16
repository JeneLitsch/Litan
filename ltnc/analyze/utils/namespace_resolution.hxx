#pragma once
#include "ltnc/sst/SST.hxx"
#include "ltnc/ast/AST.hxx"
namespace ltn::c {
	enum class VariadicMode { EXACT, REQUIRED, ALLOWED, PROHIBITED };
	
	const ast::decl::Function * resolve(
		const std::vector<const ast::decl::Function *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t parameters,
		VariadicMode variadic_mode);

	const sst::decl::Definition * resolve(
		const std::vector<const sst::decl::Definition *> & definitions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);

	const sst::decl::Global * resolve(
		const std::vector<const sst::decl::Global *> & globals,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);
}