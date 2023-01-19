#pragma once
#include "ltnc/sst/SST.hxx"
#include "ltnc/transpile/lang/Language.hxx"
#include "ltnc/transpile/lang/Cpp.hxx"
#include "ltnc/Reporter.hxx"

namespace ltn::c {
	std::string transpile(const sst::Program & program, const lang::Language &);

	// Functional
	std::string transpile_functional(const sst::Functional &, unsigned indentation, const lang::Language &);

	// Statement
	std::string transpile_statement(const sst::Statement &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::Block &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::Return &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::AssignLocal &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::AssignIndex &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::AssignMember &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::AssignGlobal &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::Throw &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::InitMember &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::IfElse &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::InfiniteLoop &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::While &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::For &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::NewVar &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::StmtSwitch &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::StatementExpression &, unsigned indentation, const lang::Language &);
	std::string transpile_stmt(const sst::DoNothing &, unsigned indentation, const lang::Language &);

	// Expression
	std::string transpile_expression(const sst::Expression &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Lambda &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::ExprSwitch &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Ternary &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Binary &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Unary &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Integer &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Float &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Bool &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Char &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Null &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::String &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Array &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Tuple &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Call &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Invoke &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Index &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::FxPointer &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Iife &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Var &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Member &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::GlobalVar &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::TypedUnary &, unsigned indentation, const lang::Language &);
	std::string transpile_expr(const sst::Reflect &, unsigned indentation, const lang::Language &);
}