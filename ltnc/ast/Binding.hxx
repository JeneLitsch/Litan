#pragma once
#include "Node.hxx"

namespace ltn::c::ast {
	struct Binding : public Node {
		Binding(const SourceLocation & location)
			: Node {location} {}
	};



	struct BraceBinding : public Binding {
		BraceBinding(const SourceLocation & location)
			: Binding {location} {}
		
		std::vector<std::unique_ptr<Binding>> sub_bindings;
	};



	struct VarBinding : public Binding {
		VarBinding(const SourceLocation & location, std::string name)
			: Binding {location}
			, name{std::move(name)} {}
		
		std::string name;
	};



	auto visit_binding(const Binding & binding, auto && fx) {
		if(auto b = as<BraceBinding>(binding)) return fx(*b);
		if(auto b = as<VarBinding>(binding)) return fx(*b);
		throw std::runtime_error{"Unknown AST binding"};
	}
}