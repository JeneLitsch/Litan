#pragma once
#include "ltnc/type/Type.hxx"
namespace ltn::c::compile {
	struct FxSignature {
		type::Type returnType;
		std::string name;
		std::vector<type::Type> parameters;
		std::string id;
	};

}