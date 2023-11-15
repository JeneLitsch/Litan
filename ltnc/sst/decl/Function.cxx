#include "Function.hxx"
#include "ltnc/sst/expr/Var.hxx"
#include "ltnc/sst/stmt/Statement.hxx"

namespace ltn::c::sst::decl {

	Function::Function(
		const Label & label,
		const std::string & name,
		Namespace namespaze,
		misc::Parameters parameters,
		stmt_ptr && body)
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