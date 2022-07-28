#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include "ltnc/ast/Ast.hxx"

namespace ltn::c {
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