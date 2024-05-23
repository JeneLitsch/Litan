#include "Scope.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/analyze/error.hxx"

#include "ltnc/analyze/utils/FunctionQueue.hxx"

namespace ltn::c {
	void Scope::set_return(const std::string & return_point) {
		this->return_point = return_point;
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



	stx::optref<const sst::decl::Global> Scope::resolve_global_variable(
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



	void Scope::require_function(stx::reference<const ast::decl::Function> fx) {
		return this->get_context().fx_queue.stage_function(fx);
	}

	
	
	void Scope::require_function(StagedFunction staged) {
		return this->get_context().fx_queue.stage_function(staged);
	}



	const std::vector<const ast::decl::Function *> & Scope::get_all_functions() const {
		return this->get_context().fx_table.get_symbols();
	}
}

