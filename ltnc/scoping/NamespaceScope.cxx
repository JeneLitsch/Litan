#include "NamespaceScope.hxx"
#include <iostream>

namespace ltn::c {
	NamespaceScope::NamespaceScope(stx::reference<const GlobalScope> parent, const Namespace & namespaze)
		: GlobalScope {}
		, namespaze { namespaze } 
		, parent { parent }
		{
		std::cout << "NAMESPACE SCOPE:" << namespaze.to_string() << "\n";
	}
	
	
	
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
		
		if(auto result = find_function(name, ns, arity, var_mode)) {
			return *result->ast_node;
		}
		else {
			return parent->resolve_function(name, ns, arity, var_mode);
		}
	}



	stx::optref<const sst::decl::Global> NamespaceScope::resolve_global_variable(
		const std::string & name,
		const Namespace & ns) const {
		
		if(auto result = find_global_variable(name, ns)) {
			return *result->ast_node;
		}
		else {
			return parent->resolve_global_variable(name, ns);
		}
	}



	stx::optref<const sst::decl::Definition> NamespaceScope::resolve_definiton(
		const std::string & name,
		const Namespace & ns) const {

		if(auto result = find_definiton(name, ns)) {
			return *result->ast_node;
		}
		else {
			return parent->resolve_definiton(name, ns);
		}
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
		return add_namespace_impl(ns, 0);
	}



	NamespaceScope & NamespaceScope::add_namespace_impl(const Namespace & ns, std::uint64_t i) {
		if(ns.size() == i) {
			return *this;
		}
		for(auto & child : this->children) {
			if(child->get_namespace_name() == ns[i]) {
				return child->add_namespace_impl(ns, i+1);
			}
		}
		auto subnamespace = Namespace{std::vector<std::string>{std::begin(ns), std::begin(ns) + i + 1}};
		this->children.push_back(std::make_unique<NamespaceScope>(*this, subnamespace));
		return this->children.back()->add_namespace_impl(ns, i+1);
	}



	namespace {
		bool match(
			const ast::decl::Function & fx,
			const std::string_view name,
			const std::size_t arity,
			VariadicMode variadic_mode) {
				
			using VM = VariadicMode; 
			switch (variadic_mode) {

			case VM::EXACT:
				return
					fx.name == name &&
					std::size(fx.parameters.simple) == arity &&
					fx.parameters.variadic;
			
			case VM::REQUIRED:
				return
					fx.name == name &&
					std::size(fx.parameters.simple) <= arity &&
					fx.parameters.variadic;
			
			case VM::ALLOWED:
				return
					match(fx, name, arity, VM::REQUIRED) ||
					match(fx, name, arity, VM::PROHIBITED);
			
			case VM::PROHIBITED:
				return
					fx.name == name &&
					std::size(fx.parameters.simple) == arity &&
					!fx.parameters.variadic;
			}

			return false;
		}



		bool match(
			const sst::decl::Definition & definition,
			const std::string_view name) {

			return definition.name == name;
		}


		
		bool match(
			const sst::decl::Global & global,
			const std::string_view name) {

			return global.name == name;
		}
	}



	stx::optref<const FunctionInfo> NamespaceScope::find_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode variadic_mode) const {
		if(ns.empty()) {
			for(stx::optref info : this->functions) {
				if(match(info->ast_node, name, arity, variadic_mode)) {
					return info;
				}
			}
			return stx::nullref;
		}
		else {
			for(auto & child : this->children) {
				if(child->get_namespace_name() == ns[0]) {
					Namespace sub_namespace { std::vector<std::string>{std::begin(ns) + 1, std::end(ns)} };
					return child->find_function(name, sub_namespace, arity, variadic_mode);
				}
			}
			return stx::nullref;
		}
	}



	stx::optref<const GlobalVariableInfo> NamespaceScope::find_global_variable(const std::string & name, const Namespace & ns) const {
		if(ns.empty()) {
			for(stx::optref info : this->variables) {
				if(match(info->ast_node, name)) {
					return info;
				}
			}
			return stx::nullref;
		}
		else {
			for(auto & child : this->children) {
				if(child->get_namespace_name() == ns[0]) {
					Namespace sub_namespace { std::vector<std::string>{std::begin(ns) + 1, std::end(ns)} };
					return child->find_global_variable(name, sub_namespace);
				}
			}
			return stx::nullref;
		}
	}


	
	stx::optref<const DefinitionInfo> NamespaceScope::find_definiton(const std::string & name, const Namespace & ns) const {
		if(ns.empty()) {
			for(stx::optref info : this->definitions) {
				if(match(info->ast_node, name)) {
					return info;
				}
			}
			return stx::nullref;
		}
		else {
			for(auto & child : this->children) {
				if(child->get_namespace_name() == ns[0]) {
					Namespace sub_namespace { std::vector<std::string>{std::begin(ns) + 1, std::end(ns)} };
					return child->find_definiton(name, sub_namespace);
				}
			}
			return stx::nullref;
		}
	}



	FunctionInfo NamespaceScope::add_function(stx::reference<const ast::decl::Function> function) {
		this->functions.push_back( FunctionInfo { .ast_node = function } );
		std::cout << function->namespaze.to_string() << function->name << " " << std::size(this->functions) << "\n";
		return this->functions.back();
	}



	GlobalVariableInfo NamespaceScope::add_global_variable(stx::reference<const sst::decl::Global> var) {
		this->variables.push_back( GlobalVariableInfo { .ast_node = var } );
		return this->variables.back();
	}
	
	
	
	DefinitionInfo NamespaceScope::add_definition(stx::reference<const sst::decl::Definition> def) {
		this->definitions.push_back( DefinitionInfo { .ast_node = def } );
		std::cout << def->namespaze.to_string() << " " << def->name << " -> " << this->namespaze.to_string() << " " << std::size(this->definitions) << "\n";
		return this->definitions.back();
	}
}