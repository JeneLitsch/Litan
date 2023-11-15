#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c {
	void optimize_definition(sst::decl::Definition & definition) {
		definition.expr = optimize_expression(std::move(definition.expr));
	}
	

	
	void optimize_function(sst::decl::Function & function) {
		function.body = optimize_statement(std::move(function.body));
	}
}