#pragma once
#include "ltnc/sst/SST.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	CompilerError undefined_function(const std::string_view & name, const SourceLocation & location);
	CompilerError undefined_function(const ast::Var & node);
	CompilerError undefined_function(const ast::FxPointer & node);
	CompilerError undefined_template(const std::string_view & name, const SourceLocation & location);

	CompilerError const_call_violation(const ast::Node & node);
	CompilerError const_assign_violation(const ast::Node & node);
	CompilerError private_call_violation(const ast::Node & node);

	CompilerError undefined_variable(const ast::Var & var);
	CompilerError redefined_variable(const std::string & name, const SourceLocation & location);

	CompilerError undefined_global(const ast::Static & global);

	CompilerError cannot_unpack_tuple(const ast::Node & node);

	CompilerError left_side_not_assignable(const ast::Node & node);
}