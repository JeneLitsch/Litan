#pragma once
#include <sstream>
#include <span>
#include "ltnc/transpile/OutputFile.hxx"
#include "ltnc/sst/SST.hxx"
#include "syntax.hxx"

namespace ltn::c::trans::c {
	
	std::vector<OutputFile> transpile_c(const sst::Program & program);

	// Functional
	Node transpile_c_functional(const sst::Functional &);

	// Statement
	Node transpile_c_statement(const sst::Statement &);
	Node transpile_c_stmt(const sst::Block &);
	Node transpile_c_stmt(const sst::Return &);
	Node transpile_c_stmt(const sst::Throw &);
	Node transpile_c_stmt(const sst::IfElse &);
	Node transpile_c_stmt(const sst::InfiniteLoop &);
	Node transpile_c_stmt(const sst::While &);
	Node transpile_c_stmt(const sst::ForEach &);
	Node transpile_c_stmt(const sst::Assign &);
	Node transpile_c_stmt(const sst::Switch &);

	// Expression
	Node transpile_c_expression(const sst::Expression &);
	Node transpile_c_expr(const sst::Choose &);
	Node transpile_c_expr(const sst::Ternary &);
	Node transpile_c_expr(const sst::Binary &);
	Node transpile_c_expr(const sst::Unary &);
	Node transpile_c_expr(const sst::Integer &);
	Node transpile_c_expr(const sst::Float &);
	Node transpile_c_expr(const sst::Bool &);
	Node transpile_c_expr(const sst::Char &);
	Node transpile_c_expr(const sst::Null &);
	Node transpile_c_expr(const sst::String &);
	Node transpile_c_expr(const sst::Array &);
	Node transpile_c_expr(const sst::Tuple &);
	Node transpile_c_expr(const sst::Call &);
	Node transpile_c_expr(const sst::Invoke &);
	Node transpile_c_expr(const sst::InvokeMember &);
	Node transpile_c_expr(const sst::Index &);
	Node transpile_c_expr(const sst::FxPointer &);
	Node transpile_c_expr(const sst::Iife &);
	Node transpile_c_expr(const sst::Var &);
	Node transpile_c_expr(const sst::Member &);
	Node transpile_c_expr(const sst::GlobalVar &);
	Node transpile_c_expr(const sst::Reflect &);
	Node transpile_c_expr(const sst::InitStruct &);
	Node transpile_c_expr(const sst::Map &);
	Node transpile_c_expr(const sst::Type &);
}	