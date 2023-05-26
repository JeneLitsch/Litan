#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"
#include "utils/Context.hxx"
#include "ltnc/make_jump_id.hxx"
#include "ltnc/labels.hxx"

#include "utils/Scope.hxx"
#include "utils/FunctionScope.hxx"
#include "utils/MajorScope.hxx"
#include "utils/MinorScope.hxx"

#include "error.hxx"

namespace ltn::c {
	sst::Program analyze(const ast::Program & program, Reporter & reporter);

	sst::func_ptr analyze_functional(
		const ast::Functional &,
		FunctionScope &,
		std::optional<Label> override_label = std::nullopt,
		const std::vector<std::unique_ptr<ast::Var>> & captures = {});
	
	sst::glob_ptr analyze_global(const ast::Global &, Context &);
	sst::defn_ptr analyze_definition(const ast::Definition &, Context &);
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::Enumeration &);

	sst::stmt_ptr analyze_statement(const ast::Statement &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Block &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Return &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Assign &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Throw &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::IfElse &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::InfiniteLoop &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::While &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::ForEach &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::NewVar &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Switch &, Scope &);

	std::vector<sst::expr_ptr> analyze_all_expressions(const std::vector<ast::expr_ptr> &, Scope &);

	sst::expr_ptr analyze_expression(const ast::Expression &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Lambda &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Choose &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Ternary &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Binary &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Unary &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Integer &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Float &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Bool &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Char &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Null &, Scope &);
	sst::expr_ptr analyze_expr(const ast::String &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Array &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Tuple &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Call &, Scope &);
	sst::expr_ptr analyze_expr(const ast::InvokeMember &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Index &, Scope &);
	sst::expr_ptr analyze_expr(const ast::FxPointer &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Iife &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Var &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Member &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Reflect &, Scope &);
	sst::expr_ptr analyze_expr(const ast::InitStruct &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Map &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Type &, Scope &);

	sst::bind_ptr analyze_binding(const ast::Binding &, Scope &);
}	