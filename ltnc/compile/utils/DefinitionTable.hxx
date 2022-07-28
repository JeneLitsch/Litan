#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
namespace ltn::c {
	// Holds and resolves functions at compile time
	class DefinitionTable {
	public:
		const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to);

		const ast::Definition * resolve(
			const std::string_view name,
			const ast::Namespace & full);

		void insert(const ast::Definition & fx);
	private:
		std::vector<const ast::Definition *> enums;
	};
}