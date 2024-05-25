#include "NamespaceScope.hxx"

namespace ltn::c {
	NamespaceScope::NamespaceScope(stx::reference<const GlobalScope> parent, const Namespace & namespaze)
		: GlobalScope {}
		, parent { parent }
		, namespaze { namespaze } {}
	
	
	
	std::uint64_t NamespaceScope::size() const {
		return parent->size();
	}



	bool NamespaceScope::is_const() const {
		return parent->is_const();
	}



	bool NamespaceScope::is_coroutine() const {
		return parent->is_coroutine();
	}



	const Namespace & NamespaceScope::get_namespace() const {
		return namespaze;
	}


	std::optional<std::string> NamespaceScope::get_return() const {
		return parent->get_return();
	}



	Context & NamespaceScope::get_context() const {
		return parent->get_context();
	}



	LocalVariableInfo NamespaceScope::declare_local_variable(const std::string & name, const SourceLocation & location) {
		throw std::runtime_error { "Cannot declare local varaible in namespace scope" };
	}


	stx::optref<const LocalVariableInfo> NamespaceScope::resolve_local_variable(const std::string & name, const SourceLocation & location) const {
		return parent->resolve_local_variable(name, location);
	}



	stx::optref<const ast::decl::Function> NamespaceScope::resolve_function(
		const std::string & name,
		const Namespace & ns,
		std::size_t arity,
		VariadicMode var_mode) const {

		auto & context = this->get_context();
		auto * fx = context.fx_table.resolve(name, this->get_namespace(), ns, arity, var_mode);
		return stx::to_optref(fx);
	}



	stx::optref<const sst::decl::Global> NamespaceScope::resolve_global_variable(
		const std::string & name,
		const Namespace & ns) const {
		
		auto & context = this->get_context();
		auto * glob = context.global_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(glob);
	}



	stx::optref<const sst::decl::Definition> NamespaceScope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		auto & context = this->get_context();
		auto * def = context.definition_table.resolve(name, this->get_namespace(), ns);
		return stx::to_optref(def);
	}



	std::uint64_t NamespaceScope::resolve_member_id(const std::string & name) const {
		return parent->resolve_member_id(name);
	}



	sst::expr_ptr NamespaceScope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return parent->resolve_custom_literal(type, value);
	}



	const std::string & NamespaceScope::get_namespace_name() const {
		if(this->namespaze.empty()) return "";
		return this->namespaze[this->namespaze.size()-1];
	}



	NamespaceScope & NamespaceScope::add_namespace(const Namespace & ns) {
		if(ns.empty()) {
			return *this;
		}
		Namespace sub_namespace {std::vector<std::string> { std::begin(ns) + 1, std::end(ns) }};
		for(auto & child : this->children) {
			if(child->get_namespace_name() == ns[0]) {
				return child->add_namespace(sub_namespace);
			}
		}
		this->children.push_back(std::make_unique<NamespaceScope>(*this, sub_namespace));
		return this->children.back()->add_namespace(sub_namespace);
	}
}