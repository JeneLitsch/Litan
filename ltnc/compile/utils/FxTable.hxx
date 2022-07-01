#pragma once
#include "ltnc/ast/Ast.hxx"
#include <vector>
namespace ltn::c {
	// Holds and resolves functions at compile time
	class FxTable {
	public:
		const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::size_t parameters);

		const ast::Functional * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			const std::size_t parameters);

		void insert(const ast::Functional & fx);
	private:
		std::vector<const ast::Functional *> functions;
	};
}