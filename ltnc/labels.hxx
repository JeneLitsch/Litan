#pragma once
#include <string>
#include "ltnc/Namespace.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	Label make_lambda_label(
		const ast::Lambda & lambda);

	Label make_function_label(
		const ast::Functional & fx);
	
	Label make_function_label(
		const Namespace & namespaze,
		const std::string & name,
		std::uint64_t arity);

	Label make_template_label(
		const ast::FunctionTemplate & tmpl,
		const std::vector<type::Type> & args);



	Label derive_template(
		const Label & label,
		const std::vector<type::Type> & args);

	Label derive_skip(
		const Label & label);
	
	Label derive_except(
		const Label & label);
}