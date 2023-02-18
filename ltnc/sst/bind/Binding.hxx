#pragma once
#include <vector>
#include <memory>
#include <numeric>
#include "ltn/Visitor.hxx"
#include "ltnc/sst/Node.hxx"

namespace ltn::c::sst {
	struct Expression;
	
	struct GroupBinding;
	struct NewVarBinding;
	struct NoBinding;
	struct GlobalBinding;
	struct MemberBinding;
	struct LocalBinding;
	struct IndexBinding;

	
	
	using BindVisitor = Visitor<
		GroupBinding,
		NewVarBinding,
		NoBinding,
		GlobalBinding,
		MemberBinding,
		LocalBinding,
		IndexBinding
	>;



	struct Binding : public Node {
		Binding() : Node {} {}

		virtual std::size_t alloc_count() const = 0;
	
		virtual void accept(const BindVisitor &) const = 0;
	};



	struct GroupBinding : public Binding {
		GroupBinding()
			: Binding {} {}

		virtual std::size_t alloc_count() const override {
			return std::accumulate(
				std::begin(this->sub_bindings),
				std::end(this->sub_bindings),
				std::size_t{0},
				[] (const auto & curr, const std::unique_ptr<Binding> & bind){
					return curr + bind->alloc_count();
				}
			);		
		}

		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<std::unique_ptr<Binding>> sub_bindings;
	};



	struct NewVarBinding : public Binding {
		NewVarBinding(std::uint64_t address)
			: Binding {}
			, address{std::move(address)} {}

		virtual std::size_t alloc_count() const override {
			return 1;
		}
		
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint64_t address;
	};



	struct NoBinding : public Binding {
		NoBinding() : Binding {} {}
		
		virtual std::size_t alloc_count() const override {
			return 0;
		}
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	struct GlobalBinding final : public Binding {
		GlobalBinding(std::uint64_t address)
			: Binding{}
			, address{address} {}

		virtual std::size_t alloc_count() const override { return 0; }
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint64_t address;
	};



	struct MemberBinding final : public Binding {
		MemberBinding(
			std::unique_ptr<Expression> object,
			std::uint64_t address)
			: Binding{}
			, object{std::move(object)}
			, address{address} {}

		virtual std::size_t alloc_count() const override { return 0; }

		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> object;
		std::uint64_t address;
	};



	struct LocalBinding final : public Binding {
		LocalBinding(
			std::uint64_t address)
			: Binding{}
			, address{address} {}

		virtual std::size_t alloc_count() const override { return 0; }
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint64_t address;
	};



	struct IndexBinding final : public Binding {
		IndexBinding(
			std::unique_ptr<Expression> range,
			std::unique_ptr<Expression> index)
			: Binding{}
			, range{std::move(range)}
			, index{std::move(index)} {}

		virtual std::size_t alloc_count() const override { return 0; }
	
		virtual void accept(const BindVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> range;
		std::unique_ptr<Expression> index;
	};



	auto visit_binding(const Binding & binding, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, GroupBinding>;
		using Base = FunctionVisitor<BindVisitor, Callable, Ret>;
		
		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			
			virtual void visit(const GroupBinding & x)  const override { this->run(x); };
			virtual void visit(const NewVarBinding & x) const override { this->run(x); };
			virtual void visit(const NoBinding & x)     const override { this->run(x); };
			virtual void visit(const GlobalBinding & x) const override { this->run(x); };
			virtual void visit(const MemberBinding & x) const override { this->run(x); };
			virtual void visit(const LocalBinding & x)  const override { this->run(x); };
			virtual void visit(const IndexBinding & x)  const override { this->run(x); };
		};

		return Visitor{fx}(binding);
	}
}