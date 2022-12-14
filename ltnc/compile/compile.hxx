#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"
#include "ltnc/compile/utils/CompilerInfo.hxx"
#include "utils/StmtResult.hxx"
#include "utils/ExprResult.hxx"

#include "ltnc/type/Type.hxx"
#include "ltnc/type/to_string.hxx"
#include "ltnc/type/deduction.hxx"

#include "utils/Scope.hxx"
#include "utils/FunctionScope.hxx"
#include "utils/MajorScope.hxx"
#include "utils/MinorScope.hxx"

#include "instantiate_type.hxx"

namespace ltn::c {

	std::unique_ptr<sst::Function> analyze_function(const ast::Function &, CompilerInfo &, Scope &);
	sst::func_ptr analyze_functional(const ast::Functional &, CompilerInfo &);
	sst::ftmp_ptr analyze_function_template(const ast::FunctionTemplate &, CompilerInfo &);
	
	sst::glob_ptr analyze_global(const ast::Global &, CompilerInfo &);
	sst::defn_ptr analyze_definition(const ast::Definition &, CompilerInfo &);
	sst::func_ptr analyze_preset(const ast::Preset &);
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::Enumeration &);

	sst::stmt_ptr analyze_statement(const ast::Statement &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Block &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Return &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Assign &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Throw &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::InitMember &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::IfElse &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::InfiniteLoop &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::While &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::For &, CompilerInfo &, Scope &);
	std::unique_ptr<sst::NewVar> analyze_stmt(const ast::NewVar &, CompilerInfo &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::StmtSwitch &, CompilerInfo &, Scope &);

	sst::expr_ptr analyze_expression(const ast::Expression &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Lambda &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::ExprSwitch &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Ternary &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Binary &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Unary &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Integer &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Float &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Bool &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Char &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Null &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::String &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Array &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Call &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Index &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::FxPointer &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Iife &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Var &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Member &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::GlobalVar &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::TypedUnary &, CompilerInfo &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Reflect &, CompilerInfo &, Scope &);

	// Functional
	InstructionBuffer compile_functional(const sst::Functional &, CompilerInfo &);
	InstructionBuffer compile_function_template(const sst::FunctionTemplate &, CompilerInfo &, const std::vector<type::Type> & arguments);

	// Statement
	InstructionBuffer compile_statement(const sst::Statement &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::Block &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::Return &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::Assign &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::Throw &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::InitMember &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::IfElse &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::InfiniteLoop &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::While &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::For &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::NewVar &, CompilerInfo &, Scope &);
	InstructionBuffer compile_stmt(const sst::StmtSwitch &, CompilerInfo &, Scope &);

	// Expression
	InstructionBuffer compile_expression(const sst::Expression &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Lambda &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::ExprSwitch &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Ternary &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Binary &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Unary &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Integer &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Float &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Bool &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Char &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Null &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::String &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Array &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Call &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Index &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::FxPointer &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Iife &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Var &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Member &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::GlobalVar &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::TypedUnary &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::Reflect &, CompilerInfo &, Scope &);
	InstructionBuffer compile_expr(const sst::DeclType &, CompilerInfo &, Scope &);
	
	InstructionBuffer compile_addr(const sst::Var &, Scope &);
	InstructionBuffer compile_write_define(const sst::Var &, CompilerInfo &, Scope &);
	InstructionBuffer compile_write_global(const sst::GlobalVar &, CompilerInfo &, Scope &);

	std::string make_template_id(
		const ast::Functional & tmpl,
		const std::vector<type::Type> & arguments
	);

	// utils
	void guard_const(
		const sst::Node &,
		const Scope &);
	
	void guard_private(
		const ast::Functional & fx,
		const Namespace & call_ns,
		const SourceLocation & loc);

	CompilerError undefined_function(
		const std::string_view & name,
		const sst::Node & node);

	InstructionBuffer compile_conditional(
		const std::string & name,
		const InstructionBuffer & condition,
		const InstructionBuffer & if_branch,
		const InstructionBuffer * else_branch);

	void add_template_args(
		Scope & scope,
		const std::vector<std::string> & template_params,
		const std::vector<type::IncompleteType> & template_args);

	void add_template_args(
		Scope & scope,
		const std::vector<std::string> & template_params,
		const std::vector<type::Type> & template_args);

	stx::reference<const ast::FunctionTemplate> get_template(
		const std::string & name,
		const Namespace & namespaze,
		const std::size_t function_arity,
		const std::size_t template_arity,
		const SourceLocation & location,
		CompilerInfo & info,
		Scope & scope);
}	