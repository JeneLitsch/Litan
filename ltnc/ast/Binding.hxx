#pragma once
#include "Node.hxx"

namespace ltn::c::ast {
	struct Binding : public Node {
		Binding(const SourceLocation & location)
			: Node {location} {}
	};



	struct GroupBinding : public Binding {
		GroupBinding(const SourceLocation & location)
			: Binding {location} {}
		
		std::vector<std::unique_ptr<Binding>> sub_bindings;
	};



	struct NewVarBinding : public Binding {
		NewVarBinding(const SourceLocation & location, std::string name)
			: Binding {location}
			, name{std::move(name)} {}
		
		std::string name;
	};



	auto visit_binding(const Binding & binding, auto && fx) {
		if(auto b = as<GroupBinding>(binding)) return fx(*b);
		if(auto b = as<NewVarBinding>(binding)) return fx(*b);
		throw std::runtime_error{"Unknown AST binding"};
	}
}