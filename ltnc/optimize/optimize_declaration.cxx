#include "optimize.hxx"
#include "ltn/casts.hxx"
#include "eval/eval_unary.hxx"
namespace ltn::c::optimize {
	void global(ast::Global & global) {
		global.expr = expression(std::move(global.expr));
	}
	
	void function(ast::Function & function) {
		function.body = statement(std::move(function.body));
	}
}