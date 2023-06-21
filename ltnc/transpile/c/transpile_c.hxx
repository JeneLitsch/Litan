#pragma once
#include <string>
#include <sstream>
#include <span>
#include "ltnc/sst/SST.hxx"
#include "print.hxx"
#include "Indent.hxx"

namespace ltn::c::trans::cxx {

	std::string transpile_c(const sst::Program & program);

	// Functional
	std::string transpile_c_functional(const sst::Functional &, Indent indent);

	// Statement
	void transpile_c_statement(const sst::Statement &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::Block &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::Return &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::Throw &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::IfElse &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::InfiniteLoop &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::While &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::ForEach &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::Assign &, std::ostream &, Indent);
	void transpile_c_stmt(const sst::Switch &, std::ostream &, Indent);

	// Expression
	void transpile_c_expression(const sst::Expression &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Choose &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Ternary &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Binary &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Unary &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Integer &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Float &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Bool &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Char &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Null &, std::ostream &, Indent);
	void transpile_c_expr(const sst::String &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Array &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Tuple &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Call &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Invoke &, std::ostream &, Indent);
	void transpile_c_expr(const sst::InvokeMember &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Index &, std::ostream &, Indent);
	void transpile_c_expr(const sst::FxPointer &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Iife &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Var &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Member &, std::ostream &, Indent);
	void transpile_c_expr(const sst::GlobalVar &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Reflect &, std::ostream &, Indent);
	void transpile_c_expr(const sst::InitStruct &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Map &, std::ostream &, Indent);
	void transpile_c_expr(const sst::Type &, std::ostream &, Indent);

	void transpile_c_binding(const sst::Binding &, std::ostream &, Indent);
}	