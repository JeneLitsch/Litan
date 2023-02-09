#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/make_jump_id.hxx"
#include "ltnc/labels.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"

#include "ltnc/type/Type.hxx"
#include "ltnc/type/to_string.hxx"
#include "ltnc/type/deduction.hxx"

#include "InstructionBuffer.hxx"
#include "ltnc/Instructions.hxx"

namespace ltn::c {
	std::tuple<std::vector<inst::Inst>, LinkInfo> compile(const sst::Program & program, Reporter & reporter);

	// Functional
	InstructionBuffer compile_functional(const sst::Functional &);

	// Statement
	InstructionBuffer compile_statement(const sst::Statement &);
	InstructionBuffer compile_stmt(const sst::Block &);
	InstructionBuffer compile_stmt(const sst::Return &);
	InstructionBuffer compile_stmt(const sst::Throw &);
	InstructionBuffer compile_stmt(const sst::InitMember &);
	InstructionBuffer compile_stmt(const sst::IfElse &);
	InstructionBuffer compile_stmt(const sst::InfiniteLoop &);
	InstructionBuffer compile_stmt(const sst::While &);
	InstructionBuffer compile_stmt(const sst::For &);
	InstructionBuffer compile_stmt(const sst::Assign &);
	InstructionBuffer compile_stmt(const sst::StmtSwitch &);

	// Expression
	InstructionBuffer compile_expression(const sst::Expression &);
	InstructionBuffer compile_expr(const sst::Lambda &);
	InstructionBuffer compile_expr(const sst::ExprSwitch &);
	InstructionBuffer compile_expr(const sst::Ternary &);
	InstructionBuffer compile_expr(const sst::Binary &);
	InstructionBuffer compile_expr(const sst::Unary &);
	InstructionBuffer compile_expr(const sst::Integer &);
	InstructionBuffer compile_expr(const sst::Float &);
	InstructionBuffer compile_expr(const sst::Bool &);
	InstructionBuffer compile_expr(const sst::Char &);
	InstructionBuffer compile_expr(const sst::Null &);
	InstructionBuffer compile_expr(const sst::String &);
	InstructionBuffer compile_expr(const sst::Array &);
	InstructionBuffer compile_expr(const sst::Tuple &);
	InstructionBuffer compile_expr(const sst::Call &);
	InstructionBuffer compile_expr(const sst::Invoke &);
	InstructionBuffer compile_expr(const sst::Index &);
	InstructionBuffer compile_expr(const sst::FxPointer &);
	InstructionBuffer compile_expr(const sst::Iife &);
	InstructionBuffer compile_expr(const sst::Var &);
	InstructionBuffer compile_expr(const sst::Member &);
	InstructionBuffer compile_expr(const sst::GlobalVar &);
	InstructionBuffer compile_expr(const sst::TypedUnary &);
	InstructionBuffer compile_expr(const sst::Reflect &);
	InstructionBuffer compile_expr(const sst::InitStruct &);
	
	InstructionBuffer compile_conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch);
}	