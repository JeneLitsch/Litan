#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c {
	void optimize_global(ast::Global & global) {
		global.expr = optimize_expression(std::move(global.expr));
	}
	
	void optimize_function(ast::Function & function) {
		function.body = optimize_statement(std::move(function.body));
	}
}