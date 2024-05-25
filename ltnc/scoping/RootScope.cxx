#include "RootScope.hxx"
#include "NamespaceScope.hxx"
#include "ltnc/ast/AST.hxx"
#include <iostream>

namespace ltn::c {
	RootScope::RootScope(stx::reference<Context> context)
		: GlobalScope {}
		, context { context } {
		
		member_info["special:add"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::ADD)};
		member_info["special:sub"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::SUB)};
		member_info["special:mlt"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::MLT)};
		member_info["special:div"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::DIV)};
		member_info["special:mod"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::MOD)};
		member_info["special:pow"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::POW)};
		member_info["special:cmp"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::CMP)};
		member_info["special:str"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::STR)};
		member_info["special:bool"] = MemberInfo {.id = static_cast<std::uint64_t>(MemberCode::BOOL)};
	}



	std::uint64_t RootScope::size() const {
		return 0;
	}



	bool RootScope::is_const() const {
		return true;
	}



	bool RootScope::is_coroutine() const {
		return false;
	}
	
	

	const Namespace & RootScope::get_namespace() const {
		return {};
	}
	
	
	
	std::optional<std::string> RootScope::get_return() const {
		return std::nullopt;
	}
	
	

	Context & RootScope::get_context() const {
		return context;
	}
	
	

	LocalVariableInfo RootScope::declare_local_variable(const std::string & name, const SourceLocation & location) {
		throw std::runtime_error { "Cannot declare local varaible in global scope" };
	}



	FunctionInfo RootScope::declare_function(stx::reference<const ast::decl::Function> function) {
		auto & namespace_scope = this->add_namespace(function->namespaze);
		std::cout << function->namespaze.to_string() << function->name << " -> " << namespace_scope.get_namespace().to_string() << "\n";
		return namespace_scope.add_function(function);
	}



	stx::optref<const LocalVariableInfo> RootScope::resolve_local_variable(const std::string & name, const SourceLocation & location) const {
		return stx::nullref;
	}



	stx::optref<const ast::decl::Function> RootScope::resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode) const {
		return stx::nullref;
	}



	stx::optref<const sst::decl::Global> RootScope::resolve_global_variable(const std::string & name, const Namespace & ns) const {
		return stx::nullref;
	}



	stx::optref<const sst::decl::Definition> RootScope::resolve_definiton(const std::string & name, const Namespace & ns) const {
		return stx::nullref;
	}



	std::uint64_t RootScope::resolve_member_id(const std::string & name) const {
		if(member_info.contains(name)) {
			return member_info.at(name).id;
		}
		const auto id = member_info.size() + 256;
		member_info.insert({name, MemberInfo {
			.id = id,
		}});
		return id;
	}



	sst::expr_ptr RootScope::resolve_custom_literal(const std::string & type, const std::string & value) const {
		return this->get_context().custom_resolver.resolve(type, value);
	}



	NamespaceScope & RootScope::add_namespace(const Namespace & ns) {
		if(!root_namespace) {
			root_namespace = std::make_unique<NamespaceScope>(*this, Namespace{});
		}
		return root_namespace->add_namespace(ns);
	}
}