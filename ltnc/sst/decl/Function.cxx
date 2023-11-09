#include "Function.hxx"
#include "ltnc/sst/expr/Var.hxx"
#include "ltnc/sst/stmt/Statement.hxx"

namespace ltn::c::sst {
	Except::Except(
		const std::string & errorname,
		std::unique_ptr<stmt::Statement> && body)
		: body(std::move(body))
		, errorname(errorname) {}



	Except::~Except() {}



	Function::Function(
		const Label & label,
		const std::string & name,
		Namespace namespaze,
		Parameters parameters,
		std::unique_ptr<stmt::Statement> && body)
		: Declaration(name, namespaze)
		, parameters{std::move(parameters)}
		, label{std::move(label)}
		, body{std::move(body)} {}



	const std::string & Function::get_resolve_name() const {
		return this->name;
	}



	const Namespace & Function::get_resolve_namespace() const {
		return this->namespaze;
	}



	Function::~Function() {}
}