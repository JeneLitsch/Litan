#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc_core/Config.hxx"
#include "ltnc_core/CompilerError.hxx"
#include "ltnc_core/Reporter.hxx"
#include "ltnc_core/ast/Ast.hxx"
#include "ltnc_core/compile/utils/CompilerInfo.hxx"
#include "utils/StmtCode.hxx"
#include "utils/ExprCode.hxx"
#include "utils/Instructions.hxx"

namespace ltn::c::compile {
	// Functional
	InstructionBuffer functional(const ast::Functional &, CompilerInfo &);
	ExprCode lambda(const ast::Lambda &, CompilerInfo &, Scope &);

	// Statement
	StmtCode statement(const ast::Statement &, CompilerInfo &, Scope &);
	StmtCode block(const ast::Block &, CompilerInfo &, Scope &);
	StmtCode reTurn(const ast::Return &, CompilerInfo &, Scope &);
	StmtCode assign(const ast::Assign &, CompilerInfo &, Scope &);
	StmtCode modify(const ast::Modify &, CompilerInfo &, Scope &);
	StmtCode thr0w(const ast::Throw &, CompilerInfo &, Scope &);
	StmtCode init_member(const ast::InitMember &, CompilerInfo &, Scope &);
	StmtCode if_else(const ast::IfElse &, CompilerInfo &, Scope &);
	StmtCode infinite_loop(const ast::InfiniteLoop &, CompilerInfo &, Scope &);
	StmtCode while_loop(const ast::While &, CompilerInfo &, Scope &);
	StmtCode for_loop(const ast::For &, CompilerInfo &, Scope &);
	StmtCode new_variable(const ast::NewVar &, CompilerInfo &, Scope &);
	StmtCode stmt_switch(const ast::StmtSwitch &, CompilerInfo &, Scope &);

	// Expression
	ExprCode expression(const ast::Expression &, CompilerInfo &, Scope &);
	ExprCode expr_switch(const ast::ExprSwitch &, CompilerInfo &, Scope &);
	ExprCode ternary(const ast::Ternary &, CompilerInfo &, Scope &);
	ExprCode binary(const ast::Binary &, CompilerInfo &, Scope &);
	ExprCode unary(const ast::Unary &, CompilerInfo &, Scope &);
	ExprCode integer(const ast::Integer &);
	ExprCode floating(const ast::Float &);
	ExprCode boolean(const ast::Bool &);
	ExprCode character(const ast::Char &);
	ExprCode null(const ast::Null &);
	ExprCode string(const ast::String &);
	ExprCode array(const ast::Array &, CompilerInfo &, Scope &);
	ExprCode call(const ast::Call &, CompilerInfo &, Scope &);
	ExprCode index(const ast::Index &, CompilerInfo &, Scope &);
	ExprCode fxPointer(const ast::FxPointer &, CompilerInfo &, Scope &);
	ExprCode invokation(const ast::Invokation &, CompilerInfo &, Scope &);
	ExprCode iife(const ast::Iife &, CompilerInfo &, Scope &);
	ExprCode index(const ast::Index &, CompilerInfo &, Scope &);
	ExprCode global_value(const ast::GlobalValue &, CompilerInfo &, Scope &);
	ExprCode addr(const ast::Var &, Scope &);
	ExprCode read_variable(const ast::Var & expr, CompilerInfo &, Scope &);
	ExprCode read_member_access(const ast::Member &, CompilerInfo &, Scope &);

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

	InstructionBuffer conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch);
}	