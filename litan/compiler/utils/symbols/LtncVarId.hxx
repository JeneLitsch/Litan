#pragma once
#include <string>
namespace ltnc {
	struct VarId {
		VarId (const std::string & name) 
			: name(name) {}
		std::string name;
	};
}