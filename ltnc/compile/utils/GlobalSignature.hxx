#pragma once
#include <string>
#include "ltnc_core/ast/Ast.hxx"
namespace ltn::c::compile {
	struct GlobalSignature {
		std::string name;
		ast::Namespace namespaze;
		ast::Expression * constant;
	};

}