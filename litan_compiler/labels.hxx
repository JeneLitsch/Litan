#pragma once
#include <string>
#include "litan_compiler/Namespace.hxx"
#include "litan_compiler/Label.hxx"
#include "litan_compiler/ast/AST.hxx"
#include "litan_compiler/sst/SST.hxx"

namespace ltn::c {
	Label make_internal_label(
		const std::string & name);

	Label make_external_label(
		const std::string & name);

	Label make_lambda_label(
		const ast::expr::Lambda & lambda);

	Label make_function_label(
		const ast::decl::Function & fx);

	Label derive_skip(
		const Label & label);
	
	Label derive_except(
		const Label & label);
}