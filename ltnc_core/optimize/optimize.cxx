#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	void optimize(ast::Program & program) {
		for(const auto & glob : program.globals) {
			global(*glob);
		}

		for(const auto & functional : program.functions) {
			if(auto fx = as<ast::Function>(*functional)) {
				function(*fx);
			}
		}
	}
}