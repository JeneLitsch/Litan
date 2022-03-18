#pragma once
#include <string>
#include "ltnc/ast/Ast.hxx"
namespace ltn::c::compile {
	struct GlobalSignature {
		std::string name;
		ast::Namespace namespaze;
		ast::ConstExpr * constant;
	};

}