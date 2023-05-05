#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	sst::expr_ptr analyze_expr(const ast::Integer & expr, Scope &) {
		return std::make_unique<sst::Integer>(expr.value);
	}



	// compiles float literal
	sst::expr_ptr analyze_expr(const ast::Float & expr, Scope &) {
		return std::make_unique<sst::Float>(expr.value);
	}



	// compiles bool literal
	sst::expr_ptr analyze_expr(const ast::Bool & expr, Scope &) {
		return std::make_unique<sst::Bool>(expr.value);
	}



	// compiles null literal
	sst::expr_ptr analyze_expr(const ast::Null &, Scope &) {
		return std::make_unique<sst::Null>();
	}


	// compiles bool literal
	sst::expr_ptr analyze_expr(const ast::Char & expr, Scope &) {
		return std::make_unique<sst::Char>(expr.value);
	}



	// compiles string literal
	sst::expr_ptr analyze_expr(const ast::String & expr, Scope &) {
		return std::make_unique<sst::String>(expr.value);
	}
}