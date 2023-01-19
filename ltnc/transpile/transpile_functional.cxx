#include "transpile.hxx"
#include <sstream>

namespace ltn::c {
	namespace {
		std::string transpile_body(
			const sst::Statement & stmt,
			unsigned indentation,
			const lang::Language & lang) {
			
			std::ostringstream oss;
			oss << lang.indent(indentation) << "// BODY" << "\n";
			return oss.str();
		}

		std::string transpile_build_in(
			const sst::BuildIn & stmt,
			unsigned indentation,
			const lang::Language & lang) {
			
			std::ostringstream oss;
			oss << lang.indent(indentation) << "// BUILD IN" << "\n";
			return oss.str();
		}
	}


	std::string transpile_functional(
		const sst::Functional & fx,
		unsigned indentation,
		const lang::Language & lang) {
		
		std::ostringstream oss;
		oss << lang.indent(indentation) << lang.fx_start(fx) << "\n";
		
		if(const sst::Function * f = dynamic_cast<const sst::Function *>(&fx)) {
		 	oss << transpile_body(*f->body, indentation + 1, lang);
		}

		if(const sst::BuildIn * b = dynamic_cast<const sst::BuildIn *>(&fx)) {
		 	oss << transpile_build_in(*b, indentation + 1, lang);
		}
		oss << lang.indent(indentation) << lang.fx_end(fx) << "\n";
		return oss.str();
	}
}