#pragma once
#include <vector>
#include "ltnc/type/Type.hxx"
#include "ltn/casts.hxx"
#include "ltnc/sst/bind/Binding.hxx"
#include "ltnc/sst/stmt/Statement.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Expression;
	
	
	using stmt_ptr = std::unique_ptr<Statement>;


	
	struct DoNothing : public Statement {
		DoNothing() : Statement{} {}
		
		virtual ~DoNothing() = default;

		virtual std::size_t nested_alloc() const override { return 0; }
		virtual std::size_t direct_alloc() const override { return 0; }

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	struct Throw final : public Statement {
		Throw(std::unique_ptr<Expression> expr) 
			: Statement{}
			, expr(std::move(expr)) {}

		virtual std::size_t nested_alloc() const override { return 0; }
		virtual std::size_t direct_alloc() const override { return this->expr->alloc(); }

		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
	};



	struct Block final : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements) 
			: Statement{}
			, statements(std::move(statements)) {}

		virtual std::size_t nested_alloc() const override {
			std::size_t nested = 0;
			std::size_t direct = 0;
			for(const auto & stmt : this->statements) {
				nested = std::max(nested, stmt->nested_alloc());
				direct += stmt->direct_alloc();
			}
			return nested + direct;
		}
		
		virtual std::size_t direct_alloc() const override {
			return 0;
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<std::unique_ptr<Statement>> statements;
	};



	struct Assign final : public Statement {
		Assign(
			std::unique_ptr<Binding> binding,
			std::unique_ptr<Expression> expr)
			: Statement{}
			, binding{std::move(binding)}
			, expr(std::move(expr)) {}

		virtual std::size_t nested_alloc() const override {
			return 0;
		}
		
		virtual std::size_t direct_alloc() const override {
			return this->binding->alloc_count() + expr->alloc();
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Binding> binding;
		std::unique_ptr<Expression> expr;
	};



	struct IfElse final : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch)
			: Statement{}
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}

		virtual std::size_t nested_alloc() const override {
			return this->else_branch
				? std::max(if_branch->nested_alloc(), else_branch->nested_alloc())
				: if_branch->nested_alloc();
		}
		
		virtual std::size_t direct_alloc() const override {
			return this->condition->alloc();
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> if_branch;
		std::unique_ptr<Statement> else_branch;
	};



	struct While final : public Statement {
		While(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body)
			: Statement{}
			, condition(std::move(condition))
			, body(std::move(body)) {}

		virtual std::size_t nested_alloc() const override {
			return body->nested_alloc();
		}
		
		virtual std::size_t direct_alloc() const override {
			return this->condition->alloc();
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};



	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::unique_ptr<Statement> body)
			: Statement{}
			, body(std::move(body)) {}

		virtual std::size_t nested_alloc() const override {
			return body->nested_alloc();
		}
		
		virtual std::size_t direct_alloc() const override {
			return 0;
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Statement> body;
	};



	struct ForEach final : public Statement {
		ForEach(
			std::size_t element_addr,
			std::size_t container_addr,
			std::size_t iterator_addr,
			std::unique_ptr<Expression> expr,
			std::unique_ptr<Statement> body)
			: element_addr(element_addr)
			, container_addr(container_addr)
			, iterator_addr(iterator_addr)
			, expr(std::move(expr))
			, body(std::move(body)) {}

		virtual std::size_t nested_alloc() const override {
			return body->nested_alloc();
		}
		
		virtual std::size_t direct_alloc() const override {
			return 3 + this->expr->alloc();
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::size_t element_addr;
		std::size_t container_addr;
		std::size_t iterator_addr;
		std::unique_ptr<Expression> expr;
		std::unique_ptr<Statement> body;
	};



	struct Return final : public Statement {
		Return(
			std::unique_ptr<Expression> expr,
			std::optional<std::string> overide_label)
			: Statement{}
			, expr(std::move(expr))
			, overide_label{overide_label} {}

		virtual std::size_t nested_alloc() const override { return 0; }
		virtual std::size_t direct_alloc() const override { return this->expr->alloc(); }
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
		std::optional<std::string> overide_label;
	};


	
	struct Switch : public Statement {
		Switch()
			: Statement{} {}

		virtual std::uint64_t nested_alloc() const override {
			return 0;
		}

		virtual std::size_t direct_alloc() const override {
			std::size_t nested = 0;
			std::size_t direct = 0;
			for(const auto & [c4se,stmt] : this->cases) {
				nested = std::max({
					nested,
					stmt->nested_alloc(),
					c4se->alloc()
				});
				direct += stmt->direct_alloc();
			}
			return nested + direct;
		}
	
		virtual void accept(const StmtVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;
		
		std::vector<std::pair<
			std::unique_ptr<Expression>,
			std::unique_ptr<Statement>
		>> cases;
		
		std::unique_ptr<Statement> d3fault;
	};



	auto visit_statement(const sst::Statement & stmt, auto && fx) {
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, Block>;
		using Base = FunctionVisitor<StmtVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			
			virtual void visit(const Block & x) const override { this->run(x); }
			virtual void visit(const IfElse & x) const override { this->run(x); }
			virtual void visit(const While & x) const override { this->run(x); }
			virtual void visit(const InfiniteLoop & x) const override { this->run(x); }
			virtual void visit(const ForEach & x) const override { this->run(x); }
			virtual void visit(const Assign & x) const override { this->run(x); }
			virtual void visit(const Return & x) const override { this->run(x); }
			virtual void visit(const Throw & x) const override { this->run(x); }
			virtual void visit(const Switch & x) const override { this->run(x); }
			virtual void visit(const DoNothing & x) const override { this->run(x); }
		};

		return Visitor{fx}(stmt);
	}
}