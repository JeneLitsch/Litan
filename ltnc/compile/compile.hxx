#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/compile/utils/CompilerInfo.hxx"
#include "utils/StmtResult.hxx"
#include "utils/ExprResult.hxx"

#include "utils/Scope.hxx"
#include "utils/MajorScope.hxx"
#include "utils/MinorScope.hxx"

namespace ltn::c {
	// Functional
	InstructionBuffer compile_functional(const ast::Functional &, CompilerInfo &);

	// Statement
	StmtResult compile_statement(const ast::Statement &, CompilerInfo &, Scope &);
	StmtResult compile_block(const ast::Block &, CompilerInfo &, Scope &);
	StmtResult compile_reTurn(const ast::Return &, CompilerInfo &, Scope &);
	StmtResult compile_assign(const ast::Assign &, CompilerInfo &, Scope &);
	StmtResult compile_thr0w(const ast::Throw &, CompilerInfo &, Scope &);
	StmtResult compile_init_member(const ast::InitMember &, CompilerInfo &, Scope &);
	StmtResult compile_if_else(const ast::IfElse &, CompilerInfo &, Scope &);
	StmtResult compile_infinite_loop(const ast::InfiniteLoop &, CompilerInfo &, Scope &);
	StmtResult compile_while_loop(const ast::While &, CompilerInfo &, Scope &);
	StmtResult compile_for_loop(const ast::For &, CompilerInfo &, Scope &);
	StmtResult compile_new_variable(const ast::NewVar &, CompilerInfo &, Scope &);
	StmtResult compile_stmt_switch(const ast::StmtSwitch &, CompilerInfo &, Scope &);

	// Expression
	ExprResult compile_expression(const ast::Expression &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Lambda &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::ExprSwitch &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Ternary &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Binary &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Unary &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Integer &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Float &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Bool &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Char &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Null &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::String &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Array &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Call &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Index &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::FxPointer &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Iife &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Var &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Member &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::GlobalVar &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::TypedUnary &, CompilerInfo &, Scope &);
	ExprResult compile_expr(const ast::Reflect &, CompilerInfo &, Scope &);

	ExprResult compile_addr(const ast::Var &, Scope &);
	ExprResult compile_write_define(const ast::Var &, CompilerInfo &, Scope &);
	ExprResult compile_write_global(const ast::GlobalVar &, CompilerInfo &, Scope &);

	// utils
	void guard_const(
		const ast::Node &,
		const Scope &);
	
	void guard_private(
		const ast::Functional & fx,
		const ast::Namespace & call_ns,
		const SourceLocation & loc);

	CompilerError undefined_function(
		const std::string_view & name,
		const ast::Node & node);

	InstructionBuffer compile_conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch);
}	