#include "Instructions.hxx"
#include <sstream>

namespace ltn::c::compile::inst {
	std::string comment(std::string msg) {
		return "// " + msg + "\n";
	}

	std::string jumpmark(const std::string_view name) {
		std::stringstream ss;
		ss << ":" << name << "\n";
		return ss.str(); 
	}
}