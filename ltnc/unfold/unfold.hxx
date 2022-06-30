#pragma once
#include "stdxx/float64_t.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/lex/Lexer.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"

namespace ltn::c::unfold {
	ast::prog_ptr source(ast::srce_ptr source);
	ast::func_ptr preset(ast::prst_ptr preset);
	std::vector<ast::glob_ptr> enumeration(ast::enum_ptr e);
}