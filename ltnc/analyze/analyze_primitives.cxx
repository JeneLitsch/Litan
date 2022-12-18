#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	sst::expr_ptr analyze_expr(const ast::Integer & expr, Context &, Scope &) {
		return std::make_unique<sst::Integer>(expr.value, type::Int{});
	}



	// compiles float literal
	sst::expr_ptr analyze_expr(const ast::Float & expr, Context &, Scope &) {
		return std::make_unique<sst::Float>(expr.value, type::Float{});
	}



	// compiles bool literal
	sst::expr_ptr analyze_expr(const ast::Bool & expr, Context &, Scope &) {
		return std::make_unique<sst::Bool>(expr.value, type::Bool{});
	}



	// compiles null literal
	sst::expr_ptr analyze_expr(const ast::Null &, Context &, Scope &) {
		return std::make_unique<sst::Null>(type::Null{});
	}


	// compiles bool literal
	sst::expr_ptr analyze_expr(const ast::Char & expr, Context &, Scope &) {
		return std::make_unique<sst::Char>(expr.value, type::Char{});
	}



	// compiles string literal
	sst::expr_ptr analyze_expr(const ast::String & expr, Context &, Scope &) {
		return std::make_unique<sst::String>(expr.value, type::String{});
	}
}