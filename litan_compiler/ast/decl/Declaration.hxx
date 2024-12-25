#pragma once
#include <map>
#include "litan_compiler/Namespace.hxx"
#include "litan_compiler/ast/Node.hxx"
#include "litan_compiler/ast/types.hxx"

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

