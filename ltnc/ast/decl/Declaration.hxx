#pragma once
#include <map>
#include "ltnc/Namespace.hxx"
#include "ltnc/ast/Node.hxx"
#include "ltnc/ast/types.hxx"

namespace ltn::c::ast::decl {
	struct Integer;


	struct Declaration : public Node {
		Declaration(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze) 
			: Node(location)
			, name(name)
			, namespaze(namespaze) {}
		virtual ~Declaration() = default;
		std::string name;
		Namespace namespaze;
	};
}

