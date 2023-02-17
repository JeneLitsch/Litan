#pragma once
#include "Node.hxx"
#include "ltn/Visitor.hxx"

namespace ltn::c::ast {
	struct GroupBinding;
	struct NewVarBinding;


	
	using BindVisitor = Visitor<
		GroupBinding,
		NewVarBinding
	>;



	struct Binding : public Node {
		Binding(const SourceLocation & location)
			: Node {location} {}

		virtual void accept(const BindVisitor &) const = 0;
	};



	struct GroupBinding final : public Binding {
		GroupBinding(const SourceLocation & location)
			: Binding {location} {}
		
		std::vector<std::unique_ptr<Binding>> sub_bindings;

		virtual void accept(const BindVisitor & visitor) const override { visitor.visit(*this); }
	};



	struct NewVarBinding final : public Binding {
		NewVarBinding(const SourceLocation & location, std::string name)
			: Binding {location}
			, name{std::move(name)} {}
		
		std::string name;

		virtual void accept(const BindVisitor & visitor) const override { visitor.visit(*this); }
	};



	auto visit_binding(const Binding & binding, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, GroupBinding>;
		using Base = FunctionVisitor<BindVisitor, Callable, Ret>;
		
		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			virtual void visit(const GroupBinding & x)  const override { this->run(x); };
			virtual void visit(const NewVarBinding & x) const override { this->run(x); };
		};

		return Visitor{fx}(binding);
	}
}