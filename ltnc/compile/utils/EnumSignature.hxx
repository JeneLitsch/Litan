#pragma once
#include <string>
#include "ltnc/ast/Ast.hxx"
namespace ltn::c::compile {
	struct EnumSignature {
		std::string name;
		ast::Namespace namespaze;
		ast::Enum * enumeration;
	};

}