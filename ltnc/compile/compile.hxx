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
	std::string functional(const ast::Functional & fx, CompilerInfo & info);
	ExprCode lambda(const ast::Lambda & lm, CompilerInfo & info, Scope & scope);

	// Statement
	StmtCode statement(const ast::Statement & stmt, CompilerInfo & info, Scope & scope);
	StmtCode if_else(const ast::IfElse & stmt, CompilerInfo & info, Scope & scope);
	StmtCode infinite_loop(const ast::InfiniteLoop & stmt, CompilerInfo & info, Scope & scope);
	StmtCode while_loop(const ast::While & stmt, CompilerInfo & info, Scope & scope);
	StmtCode for_loop(const ast::For & stmt, CompilerInfo & info, Scope & scope);
	StmtCode new_variable(const ast::NewVar & stmt, CompilerInfo & info, Scope & scope);
	StmtCode new_const(const ast::NewConst & stmt, CompilerInfo & info, Scope & scope);

	// Expression
	ExprCode expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope);
	ExprCode ternary(const ast::Ternary & expr, CompilerInfo & info, Scope & scope);
	ExprCode binary(const ast::Binary & expr, CompilerInfo & info, Scope & scope);
	ExprCode unary(const ast::Unary & expr, CompilerInfo & info, Scope & scope);
	ExprCode integer(const ast::Integer & expr);
	ExprCode floating(const ast::Float & expr);
	ExprCode boolean(const ast::Bool & expr);
	ExprCode character(const ast::Char & expr);
	ExprCode null(const ast::Null & expr);
	ExprCode string(const ast::String & expr);
	ExprCode array(const ast::Array & expr, CompilerInfo & info, Scope & scope);
	ExprCode call(const ast::Call & expr, CompilerInfo & info, Scope & scope);
	ExprCode index(const ast::Index & expr, CompilerInfo & info, Scope & scope);
	ExprCode fxPointer(const ast::FxPointer & expr, CompilerInfo & info, Scope & scope);
	ExprCode iife(const ast::Iife & expr, CompilerInfo & info, Scope & scope);
	ExprCode global_value(const ast::GlobalValue & expr, CompilerInfo & info, Scope & scope);
	ExprCode assignable(const ast::Assignable & expr, CompilerInfo & info, Scope & scope);
	ExprCode addr(const ast::Var & expr, Scope & scope);
	ExprCode read_variable(const ast::Var & expr, CompilerInfo & info, Scope & scope);
	ExprCode read_member_access(const ast::Member & access, CompilerInfo & info, Scope & scope);

	// utils
	void guard_const(const ast::Node & node, const Scope & scope);
}	