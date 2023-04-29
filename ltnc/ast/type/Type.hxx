#pragma once
#include "ltnc/ast/Node.hxx"

namespace ltn::c::ast {
	struct Type;
	using type_ptr = std::unique_ptr<Type>;

	struct Type : public Node {
		Type(
			const SourceLocation & location,
			std::string name,
			std::vector<type_ptr> sub_types = {})
			: Node { location }
			, name{ std::move(name) }
			, sub_types { std::move(sub_types) } {}
		
		std::string name;
		std::vector<type_ptr> sub_types;
	};
}