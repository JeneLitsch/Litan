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
		const SourceLocation & location) {
		if(this->vars.contains(name)) {
			throw redefined_variable(name, location);
		}
		const auto address = size();
		const Variable var{
			.address = address,
		}; 
		this->vars.insert({name, var});
		return var;
	}



	stx::optref<const ast::decl::Function> Scope::resolve_function(
		const std::string & name,
		const Namespace & ns,
		std::size_t arity,
		VariadicMode var_mode) const {

		auto & context = this->get_context();
		auto * fx = context.fx_table.resolve(name, this->get_namespace(), ns, arity, var_mode);
		return stx::to_optref(fx);
	}



	stx::optref<const sst::decl::Global> Scope::resolve_global(
		const std::string & name,
		const Namespace & ns) const {
		
		auto & context = this->get_context();
		auto * glob = context.global_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(glob);
	}



	stx::optref<const sst::decl::Definition> Scope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		auto & context = this->get_context();
		auto * def = context.definition_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(def);
	}



	std::uint64_t Scope::resolve_member_id(const std::variant<std::string, MemberCode> & name) const {
		return this->get_context().member_table.get_id(name);
	}



	sst::expr_ptr Scope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return this->get_context().custom_resolver.resolve(type, value);
	}
}

