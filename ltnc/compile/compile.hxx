#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/Ast.hxx"
#include "ltnc/compile/utils/CompilerInfo.hxx"
#include "utils/StmtCode.hxx"
#include "utils/ExprCode.hxx"

#include "utils/Scope.hxx"
#include "utils/MajorScope.hxx"
#include "utils/MinorScope.hxx"

namespace ltn::c {
	// Functional
	InstructionBuffer compile_functional(const ast::Functional &, CompilerInfo &);
	ExprCode compile_lambda(const ast::Lambda &, CompilerInfo &, Scope &);

	// Statement
	StmtCode compile_statement(const ast::Statement &, CompilerInfo &, Scope &);
	StmtCode compile_block(const ast::Block &, CompilerInfo &, Scope &);
	StmtCode compile_reTurn(const ast::Return &, CompilerInfo &, Scope &);
	StmtCode compile_assign(const ast::Assign &, CompilerInfo &, Scope &);
	StmtCode compile_modify(const ast::Modify &, CompilerInfo &, Scope &);
	StmtCode compile_thr0w(const ast::Throw &, CompilerInfo &, Scope &);
	StmtCode compile_init_member(const ast::InitMember &, CompilerInfo &, Scope &);
	StmtCode compile_if_else(const ast::IfElse &, CompilerInfo &, Scope &);
	StmtCode compile_infinite_loop(const ast::InfiniteLoop &, CompilerInfo &, Scope &);
	StmtCode compile_while_loop(const ast::While &, CompilerInfo &, Scope &);
	StmtCode compile_for_loop(const ast::For &, CompilerInfo &, Scope &);
	StmtCode compile_new_variable(const ast::NewVar &, CompilerInfo &, Scope &);
	StmtCode compile_stmt_switch(const ast::StmtSwitch &, CompilerInfo &, Scope &);

	// Expression
	ExprCode compile_expression(const ast::Expression &, CompilerInfo &, Scope &);
	ExprCode compile_expr_switch(const ast::ExprSwitch &, CompilerInfo &, Scope &);
	ExprCode compile_ternary(const ast::Ternary &, CompilerInfo &, Scope &);
	ExprCode compile_binary(const ast::Binary &, CompilerInfo &, Scope &);
	ExprCode compile_unary(const ast::Unary &, CompilerInfo &, Scope &);
	ExprCode compile_integer(const ast::Integer &);
	ExprCode compile_floating(const ast::Float &);
	ExprCode compile_boolean(const ast::Bool &);
	ExprCode compile_character(const ast::Char &);
	ExprCode compile_null(const ast::Null &);
	ExprCode compile_string(const ast::String &);
	ExprCode compile_array(const ast::Array &, CompilerInfo &, Scope &);
	ExprCode compile_call(const ast::Call &, CompilerInfo &, Scope &);
	ExprCode compile_index(const ast::Index &, CompilerInfo &, Scope &);
	ExprCode compile_fxPointer(const ast::FxPointer &, CompilerInfo &, Scope &);
	ExprCode compile_invokation(const ast::Invokation &, CompilerInfo &, Scope &);
	ExprCode compile_iife(const ast::Iife &, CompilerInfo &, Scope &);
	ExprCode compile_index(const ast::Index &, CompilerInfo &, Scope &);
	ExprCode compile_addr(const ast::Var &, Scope &);
	ExprCode compile_read_variable(const ast::Var & expr, CompilerInfo &, Scope &);
	ExprCode compile_read_member_access(const ast::Member &, CompilerInfo &, Scope &);
	ExprCode compile_read_static(const ast::GlobalVar & global, CompilerInfo & info, Scope &);
	ExprCode compile_write_static(const ast::GlobalVar & global, CompilerInfo & info, Scope &);
	ExprCode compile_read_static(const ast::DefinitionValue & def, CompilerInfo & info, Scope &);
	ExprCode compile_write_static(const ast::DefinitionValue & def, CompilerInfo & info, Scope &);

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

	CompilerError cannot_assign(
		const type::Type & from,
		const type::Type & to);
}	