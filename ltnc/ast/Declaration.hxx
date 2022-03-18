#pragma once
#include "Node.hxx"
#include "Namespace.hxx"
#include <map>

namespace ltn::c::ast {
	struct ConstExpr;



	struct Declaration : public Node {
		Declaration(const SourceLocation & location) : Node(location) {}
		virtual ~Declaration() = default;
	};



	struct Global : public Declaration {
		Global(const SourceLocation & location) : Declaration(location) {}
		virtual ~Global() = default;
		std::string name;
		Namespace namespaze;
		std::unique_ptr<ast::ConstExpr> literal;
	};
}