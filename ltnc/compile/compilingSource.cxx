#include "compiling.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "Instructions.hxx"
namespace ltn::c::compile {
	namespace {
	}

	std::string source(
		const ast::Source & program,
		const Config & config,
		SymbolTable & stable) {
		std::stringstream ss;

		for(const auto & function : program.functions) {
			ss << inst::comment("Function " + function->name);
		}
		return ss.str();
	}
}