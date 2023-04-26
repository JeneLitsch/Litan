#include "Scope.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/analyze/error.hxx"

namespace ltn::c {
	void Scope::set_return(const std::string & return_point) {
		this->return_point = return_point;
	}

	// defines new variable and prevents disambiguations
	// Variables in outer scope can not be hidden
	Variable Scope::insert(
		const std::string & name,
		const SourceLocation & location,
		const type::Type & type) {
		if(this->vars.contains(name)) {
			throw redefined_variable(name, location);
		}
		const auto address = size();
		const Variable var{
			.address = address,
			.type = type,
		}; 
		this->vars.insert({name, var});
		return var;
	}



	void Scope::add_type(const std::string & name, const type::Type & type) {
		this->type_map.insert({name, type});
	}



	void Scope::inherit_types_from(const Scope & scope) {
		for(const auto & [key, val] : scope.type_map) {
			this->type_map.insert({key, val});
		}
	}




	stx::optref<const ast::Functional> Scope::resolve_function(
		const std::string & name,
		const Namespace & ns,
		std::size_t arity) const {

		auto & context = this->get_context();
		auto * fx = context.fx_table.resolve(name, this->get_namespace(), ns, arity);
		return stx::to_optref(fx);
	}



	stx::optref<const sst::Global> Scope::resolve_global(
		const std::string & name,
		const Namespace & ns) const {
		
		auto & context = this->get_context();
		auto * glob = context.global_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(glob);
	}



	stx::optref<const sst::Definition> Scope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		auto & context = this->get_context();
		auto * def = context.definition_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(def);
	}



	std::uint64_t Scope::resolve_member_id(const std::string & name) const {
		return this->get_context().member_table.get_id(name);
	}
}

