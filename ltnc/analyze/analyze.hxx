#pragma once
#include <sstream>
#include <span>
#include "ltn/casts.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"
#include "utils/Context.hxx"
#include "ltnc/make_jump_id.hxx"
#include "ltnc/labels.hxx"

#include "ltnc/type/Type.hxx"
#include "ltnc/type/to_string.hxx"
#include "ltnc/type/deduction.hxx"

#include "utils/Scope.hxx"
#include "utils/FunctionScope.hxx"
#include "utils/MajorScope.hxx"
#include "utils/MinorScope.hxx"

#include "instantiate_type.hxx"

namespace ltn::c {
	sst::Program analyze(const ast::Program & program, Reporter & reporter);

	ast::func_ptr generate_ctor(const ast::Preset &);

	std::unique_ptr<sst::Function> analyze_function(const ast::Function &, Context &, Scope &);
	sst::func_ptr analyze_functional(const ast::Functional &, Context &);
	sst::func_ptr analyze_function_template(const ast::FunctionTemplate &, Context &, const std::vector<type::Type> & arguments);
	
	sst::glob_ptr analyze_global(const ast::Global &, Context &);
	sst::defn_ptr analyze_definition(const ast::Definition &, Context &);
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::Enumeration &);

	sst::stmt_ptr analyze_statement(const ast::Statement &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Block &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Return &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Assign &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::Throw &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::InitMember &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::IfElse &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::InfiniteLoop &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::While &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::For &, Context &, Scope &);
	std::unique_ptr<sst::NewVar> analyze_stmt(const ast::NewVar &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::StructuredBinding &, Context &, Scope &);
	sst::stmt_ptr analyze_stmt(const ast::StmtSwitch &, Context &, Scope &);

	sst::expr_ptr analyze_expression(const ast::Expression &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Lambda &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::ExprSwitch &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Ternary &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Binary &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Unary &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Integer &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Float &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Bool &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Char &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Null &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::String &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Array &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Tuple &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Call &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Index &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::FxPointer &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Iife &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Var &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Member &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::GlobalVar &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::TypedUnary &, Context &, Scope &);
	sst::expr_ptr analyze_expr(const ast::Reflect &, Context &, Scope &);

	// utils
	void guard_const(
		const ast::Node &,
		const Scope &);
	
	void guard_private(
		const ast::Functional & fx,
		const Namespace & call_ns,
		const SourceLocation & loc);

	CompilerError undefined_function(
		const std::string_view & name,
		const ast::Node & node);

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
		Context & context,
		Scope & scope);
}	