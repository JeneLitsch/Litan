#pragma once
#include <string>
#include "ltnc_core/ast/Namespace.hxx"
namespace ltn::c::compile {
	struct FxSignature {
		std::string name;
		ast::Namespace namespaze;
		std::size_t parameters;
		std::string id;
	};

}