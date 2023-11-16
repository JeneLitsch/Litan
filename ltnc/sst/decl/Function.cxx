#include "Function.hxx"
#include "ltnc/sst/expr/Var.hxx"
#include "ltnc/sst/stmt/Statement.hxx"

namespace ltn::c::sst::decl {

	Function::Function(
		const std::string & name,
		Namespace namespaze,
		stmt_ptr && body,
		const Label & label)
		: Declaration(name, namespaze)
		, label{std::move(label)}
		, body{std::move(body)} {}



	const std::string & Function::get_resolve_name() const {
		return this->name;
	}



	const Namespace & Function::get_resolve_namespace() const {
		return this->namespaze;
	}



	Function::~Function() {}




	std::unique_ptr<Function> function(
		const std::string & name,
		Namespace namespaze,
		stmt_ptr && body,
		const Label & label) {
		
		return std::make_unique<Function>(name, namespaze, std::move(body), label);
	}
}