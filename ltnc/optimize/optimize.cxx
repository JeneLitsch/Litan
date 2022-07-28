#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c {
	void optimize(ast::Program & program) {
		for(const auto & def : program.definitions) {
			optimize_definition(*def);
		}

		for(const auto & functional : program.functions) {
			if(auto fx = as<ast::Function>(*functional)) {
				optimize_function(*fx);
			}
		}
	}
}