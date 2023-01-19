#include "transpile.hxx"
#include <sstream>

namespace ltn::c {
	std::string transpile(const sst::Program & program, const lang::Language & lang) {
		std::ostringstream oss;

		for(const auto & fx : program.functions) {
			oss << transpile_functional(*fx, 0, lang);
		}

		return oss.str();
	}
}