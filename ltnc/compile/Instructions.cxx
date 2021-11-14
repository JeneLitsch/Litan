#include "Instructions.hxx"

namespace ltn::c::compile::inst {
	std::string comment(std::string msg) {
		return "// " + msg + "\n";
	}
}