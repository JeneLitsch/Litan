#pragma once
#include <string>
#include <vector>

namespace ltna {
	class StringDecoder {
	public:
		static std::string decode(const std::vector<std::string> & args);
	};
}