#pragma once
#include <string>
#include "ltnc/ast/Namespace.hxx"
namespace ltn::c::compile {
	struct FxSignature {
		std::string name;
		ast::Namespace nameSpace;
		std::size_t parameters;
		std::string id;
	};

}