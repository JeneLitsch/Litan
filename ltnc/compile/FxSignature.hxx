#pragma once
#include <string>
namespace ltn::c::compile {
	struct FxSignature {
		std::string name;
		std::size_t parameters;
		std::string id;
	};

}