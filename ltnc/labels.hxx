#pragma once
#include <string>
#include "ltnc/Namespace.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	Label make_internal_label(
		const std::string & name);

	Label make_external_label(
		const std::string & name);

	Label make_lambda_label(
		const ast::Lambda & lambda);

	Label make_function_label(
		const ast::Functional & fx);

	Label derive_skip(
		const Label & label);
	
	Label derive_except(
		const Label & label);
}