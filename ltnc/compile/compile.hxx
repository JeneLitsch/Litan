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
	ExprResult compile_lambda(const ast::Lambda &, CompilerInfo &, Scope &);

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
	ExprResult compile_expr_switch(const ast::ExprSwitch &, CompilerInfo &, Scope &);
	ExprResult compile_ternary(const ast::Ternary &, CompilerInfo &, Scope &);
	ExprResult compile_binary(const ast::Binary &, CompilerInfo &, Scope &);
	ExprResult compile_unary(const ast::Unary &, CompilerInfo &, Scope &);
	ExprResult compile_integer(const ast::Integer &);
	ExprResult compile_floating(const ast::Float &);
	ExprResult compile_boolean(const ast::Bool &);
	ExprResult compile_character(const ast::Char &);
	ExprResult compile_null(const ast::Null &);
	ExprResult compile_string(const ast::String &);
	ExprResult compile_array(const ast::Array &, CompilerInfo &, Scope &);
	ExprResult compile_call(const ast::Call &, CompilerInfo &, Scope &);
	ExprResult compile_index(const ast::Index &, CompilerInfo &, Scope &);
	ExprResult compile_fxPointer(const ast::FxPointer &, CompilerInfo &, Scope &);
	ExprResult compile_invokation(const ast::Invokation &, CompilerInfo &, Scope &);
	ExprResult compile_iife(const ast::Iife &, CompilerInfo &, Scope &);
	ExprResult compile_index(const ast::Index &, CompilerInfo &, Scope &);
	ExprResult compile_addr(const ast::Var &, Scope &);
	ExprResult compile_read_variable(const ast::Var &, CompilerInfo &, Scope &);
	ExprResult compile_read_member_access(const ast::Member &, CompilerInfo &, Scope &);
	ExprResult compile_read_static(const ast::GlobalVar &, CompilerInfo &, Scope &);
	ExprResult compile_write_static(const ast::GlobalVar &, CompilerInfo &, Scope &);
	ExprResult compile_write_static(const ast::DefinitionValue &, CompilerInfo &, Scope &);
	ExprResult compile_static_cast(const ast::StaticCast &, CompilerInfo &, Scope &);
	ExprResult compile_dynamic_cast(const ast::DynamicCast &, CompilerInfo &, Scope &);

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