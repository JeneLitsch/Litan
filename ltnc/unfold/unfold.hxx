#pragma once
#include "stdxx/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/Lexer.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"

namespace ltn::c {
	ast::prog_ptr unfold_source(ast::srce_ptr source);
	ast::func_ptr unfold_preset(ast::prst_ptr preset);
	std::vector<ast::glob_ptr> unfold_enumeration(ast::enum_ptr e);
}