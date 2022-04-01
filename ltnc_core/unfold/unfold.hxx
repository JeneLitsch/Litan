#pragma once
#include "ltn/float64_t.hxx"
#include "ltnc_core/ast/Ast.hxx"
#include "ltnc_core/lex/Lexer.hxx"
#include "ltnc_core/CompilerError.hxx"
#include "ltnc_core/Reporter.hxx"

namespace ltn::c::unfold {
	ast::prog_ptr source(ast::srce_ptr source);
	ast::func_ptr preset(ast::prst_ptr preset);
	std::vector<ast::glob_ptr> enumeration(ast::enum_ptr e);
}