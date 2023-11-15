#pragma once
#include <string>
#include <vector>

namespace ltn::c::sst::misc {
	struct Parameter {
		std::string name;
	};
	using Parameters = std::vector<Parameter>;
}