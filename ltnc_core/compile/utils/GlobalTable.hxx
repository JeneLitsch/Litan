#pragma once
#include "ltnc_core/ast/Ast.hxx"
#include <vector>
namespace ltn::c::compile {
	// Holds and resolves functions at compile time
	class GlobalTable {
	public:
		const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to);

		const ast::Global * resolve(
			const std::string_view name,
			const ast::Namespace & full);

		void insert(const ast::Global & fx);
	private:
		std::vector<const ast::Global *> enums;
	};
}