#pragma once
#include <string>
#include <vector>

namespace ltn::a {
	class StringDecoder {
	public:
		static std::string decode(const std::vector<std::string> & args);
	};
}