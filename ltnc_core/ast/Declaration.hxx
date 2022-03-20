#pragma once
#include "Node.hxx"
#include "Namespace.hxx"
#include <map>

namespace ltn::c::ast {
	struct Expression;



	struct Declaration : public Node {
		Declaration(const SourceLocation & location) : Node(location) {}
		virtual ~Declaration() = default;
	};



	struct Global final : public Declaration {
		Global(const SourceLocation & location) : Declaration(location) {}
		virtual ~Global() = default;
		std::string name;
		Namespace namespaze;
		std::unique_ptr<ast::Expression> expr;
	};
}