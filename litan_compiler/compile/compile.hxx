#pragma once
#include <sstream>
#include <span>
#include "litan_core/casts.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/make_jump_id.hxx"
#include "litan_compiler/labels.hxx"
#include "litan_compiler/ast/AST.hxx"
#include "litan_compiler/sst/SST.hxx"

#include "InstructionBuffer.hxx"
#include "litan_compiler/Instructions.hxx"

namespace ltn::c {
	inst::Program compile(const sst::Program & program);

	// Functional
	InstructionBuffer compile_function(const sst::decl::Function &);

	// Statement
	InstructionBuffer compile_statement(const sst::stmt::Statement &);
	InstructionBuffer compile_stmt(const sst::stmt::Block &);
	InstructionBuffer compile_stmt(const sst::stmt::Conditional &);
	InstructionBuffer compile_stmt(const sst::stmt::Return &);
	InstructionBuffer compile_stmt(const sst::stmt::Yield &);
	InstructionBuffer compile_stmt(const sst::stmt::Throw &);
	InstructionBuffer compile_stmt(const sst::stmt::IfElse &);
	InstructionBuffer compile_stmt(const sst::stmt::InfiniteLoop &);
	InstructionBuffer compile_stmt(const sst::stmt::While &);
	InstructionBuffer compile_stmt(const sst::stmt::ForEach &);
	InstructionBuffer compile_stmt(const sst::stmt::Assign &);
	InstructionBuffer compile_stmt(const sst::stmt::Switch &);
	InstructionBuffer compile_stmt(const sst::stmt::CoReturn &);

	// Expression
	InstructionBuffer compile_expression(const sst::expr::Expression &);
	InstructionBuffer compile_expr(const sst::expr::Switch &);
	InstructionBuffer compile_expr(const sst::expr::Ternary &);
	InstructionBuffer compile_expr(const sst::expr::Binary &);
	InstructionBuffer compile_expr(const sst::expr::Unary &);
	InstructionBuffer compile_expr(const sst::expr::Integer &);
	InstructionBuffer compile_expr(const sst::expr::Float &);
	InstructionBuffer compile_expr(const sst::expr::Bool &);
	InstructionBuffer compile_expr(const sst::expr::Null &);
	InstructionBuffer compile_expr(const sst::expr::String &);
	InstructionBuffer compile_expr(const sst::expr::Array &);
	InstructionBuffer compile_expr(const sst::expr::Tuple &);
	InstructionBuffer compile_expr(const sst::expr::Call &);
	InstructionBuffer compile_expr(const sst::expr::Conditional &);
	InstructionBuffer compile_expr(const sst::expr::Invoke &);
	InstructionBuffer compile_expr(const sst::expr::InvokeMember &);
	InstructionBuffer compile_expr(const sst::expr::Index &);
	InstructionBuffer compile_expr(const sst::expr::FxPointer &);
	InstructionBuffer compile_expr(const sst::expr::Iife &);
	InstructionBuffer compile_expr(const sst::expr::Var &);
	InstructionBuffer compile_expr(const sst::expr::Member &);
	InstructionBuffer compile_expr(const sst::expr::GlobalVar &);
	InstructionBuffer compile_expr(const sst::expr::Reflect &);
	InstructionBuffer compile_expr(const sst::expr::Struct &);
	InstructionBuffer compile_expr(const sst::expr::Map &);
	InstructionBuffer compile_expr(const sst::expr::Type &);
	
	InstructionBuffer compile_binding(const sst::bind::Binding & binding);

	InstructionBuffer compile_conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch);
}	