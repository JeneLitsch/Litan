#pragma once
#include <vector>
#include <bitset>
#include "ltn/casts.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Operations.hxx"
#include "ltnc/sst/expr/Expression.hxx"
#include "ltnc/sst/stmt/Statement.hxx"


namespace ltn::c::sst {
	struct Expression;
	struct Var;
	struct Functional;
	struct Function;
	class Statement;



	struct Ternary : public Expression {
		Ternary(
			const type::Type & type,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_branch,
			std::unique_ptr<Expression> else_branch) 
			: Expression{type}
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}

		virtual std::uint64_t alloc() const override {
			return std::max({
				condition->alloc(),
				if_branch->alloc(),
				else_branch->alloc(),
			});
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_branch;
		std::unique_ptr<Expression> else_branch;
	};




	struct Unary : public Expression {
		using Op = UnaryOp;
		Unary(
			Op op,
			std::unique_ptr<Expression> expression,
			const type::Type & type)
			: Expression{type}
			, op(op)
			, expression(std::move(expression)) {}

		virtual std::uint64_t alloc() const override {
			return this->expression->alloc();
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Op op;
		std::unique_ptr<Expression> expression;
	};



	struct Binary : public Expression {
		using Op = BinaryOp;
		Binary(
			Op op,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const type::Type & type)
			: Expression{type}
			, op(op)
			, l(std::move(l))
			, r(std::move(r)) {}

		virtual std::uint64_t alloc() const override {
			return std::max({
				l->alloc(),
				r->alloc(),
			});
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Op op;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};



	struct Reflect : public Expression {
		struct FunctionQuery {
			std::string id;
			std::string name;
			std::string full_name;
			std::size_t arity;
			bool c0nst; 
			bool pr1vate; 
			bool ext3rn; 
		};

		struct NamespaceQuery {
			Namespace namespaze;
			std::vector<FunctionQuery> functions;
		};

		struct LineQuery {
			std::uint64_t line;
		};

		struct FileQuery {
			std::string name;
		};

		struct LocationQuery {
			FileQuery file;
			LineQuery line;
		};

		struct TypeQuery {
			type::Type type;
		};

		struct ExprQuery {
			TypeQuery type_query;
		};

		using Query = std::variant<
			NamespaceQuery,
			FunctionQuery,
			FileQuery,
			LineQuery,
			LocationQuery,
			ExprQuery,
			TypeQuery
		>;

		struct Addr {
			std::uint64_t name;
			std::uint64_t full_name;
			std::uint64_t fx_ptr;
			std::uint64_t functions;
			std::uint64_t c0nst; 
			std::uint64_t pr1vate; 
			std::uint64_t ext3rn; 
			std::uint64_t file; 
			std::uint64_t line; 
			std::uint64_t type; 
		};

		Reflect(
			Query query,
			Addr addr,
			const type::Type & type)
			: Expression{type}
			, query{std::move(query)}
			, addr{addr} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Query query;
		Addr addr;
	};



	struct TypedUnary final : public Expression {
	public:
		using Op = TypedUnaryOp;
		
		TypedUnary(
			Op op,
			const type::Type & target_type,
			std::unique_ptr<Expression> expr,
			const type::Type & type)
			: Expression{type}
			, op{op}
			, target_type{target_type}
			, expr{std::move(expr)} {}

		virtual std::uint64_t alloc() const override {
			return this->expr->alloc();
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Op op;
		type::Type target_type;
		std::unique_ptr<Expression> expr;
	};



	struct Literal : public Expression {
		Literal(const type::Type & type)
			: Expression{type} {}
		virtual ~Literal() = default;
	};



	struct Integer final : public Literal {
		Integer(std::bitset<64> value, const type::Type & type)
			: Integer(static_cast<std::int64_t>(value.to_ullong()), type) {}

		Integer(std::int64_t value, const type::Type & type)
			: Literal(type)
			, value(value) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::int64_t value;
	};



	struct Float final : public Literal {
		Float(stx::float64_t value, const type::Type & type)
			: Literal(type)
			, value(value) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		stx::float64_t value;
	};



	struct Bool final : public Literal {
		Bool(bool value, const type::Type & type)
			: Literal(type)
			, value(value) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		bool value;
	};



	struct Null final : public Literal {
		Null(const type::Type & type)
			: Literal(type) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}
	};



	struct Char final : public Literal {
		Char(std::uint8_t value, const type::Type & type)
			: Literal(type)
			, value(value) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::uint8_t value;
	};



	struct String final : public Literal {
		String(const std::string & value, const type::Type & type)
			: Literal(type)
			, value(value) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string value;
	};



	struct Array final: public Literal {
		Array(const type::Type & type) : Literal(type) {}

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->elements) {
				count = std::max(elem->alloc(), count);
			}
			return count;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<std::unique_ptr<Expression>> elements;
	};


	
	struct Tuple final: public Literal {
		Tuple(const type::Type & type) : Literal(type) {}
		virtual ~Tuple() = default;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->elements) {
				count = std::max(elem->alloc(), count);
			}
			return count;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<std::unique_ptr<Expression>> elements;
	};



	struct Lambda final : public Literal {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const type::Type & type)
			: Literal(type)
			, fx(std::move(fx))
			, captures(std::move(captures)) {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};



	struct Index final : public Expression {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const type::Type & type)
			: Expression{type}
			, expression(std::move(expression))
			, index(std::move(index)) {}

		virtual std::uint64_t alloc() const override {
			return std::max({
				this->expression->alloc(),
				this->index->alloc(),
			});
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expression;
		std::unique_ptr<Expression> index;
	};



	struct Var final : public Expression {
	public:
		Var(
			std::size_t addr,
			const type::Type & type)
			: Expression{type}
			, addr{addr} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::size_t addr;
	};



	struct GlobalVar final : public Expression {
	public:
		GlobalVar(
			const type::Type & type,
			std::size_t addr)
			: Expression{type}
			, addr { addr } {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::size_t addr;
	};



	struct Member final : public Expression {
		Member(
			const type::Type & type,
			std::unique_ptr<Expression> expr,
			std::size_t addr)
			: Expression{type}
			, expr(std::move(expr))
			, addr { addr } {};

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> expr;
		std::size_t addr;
	};



	struct Iife final : public Expression {
		Iife(
			const type::Type & type,
			std::string return_label,
			std::unique_ptr<Statement> stmt,
			type::Type return_type) 
			: Expression{type}
			, return_label{return_label}
			, stmt(std::move(stmt))
			, return_type{return_type} {}

		virtual std::uint64_t alloc() const override {
			return this->stmt->direct_alloc() + this->stmt->nested_alloc();
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::string return_label;
		std::unique_ptr<Statement> stmt;
		type::Type return_type;
	};



	struct FxPointer final : public Expression {
	public:
		FxPointer(
			const Label & label,
			std::size_t arity,
			const type::Type & type)
			: Expression{type}
			, label{label}
			, arity{arity} {}

		virtual std::uint64_t alloc() const override {
			return 0;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Label label;
		std::size_t arity;
	};



	struct Call final : public Expression {
	public:
		Call(
			const Label & label,
			std::vector<std::unique_ptr<Expression>> parameters,
			const type::Type & type)
			: Expression{type}
			, label{label}
			, parameters(std::move(parameters)) {}

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->parameters) {
				count = std::max(elem->alloc(), count);
			}
			return count;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		Label label;
		std::vector<std::unique_ptr<Expression>> parameters;
	};



	struct Invoke final : public Expression {
	public:
		Invoke(
			std::unique_ptr<Expression> function_ptr,
			std::vector<std::unique_ptr<Expression>> parameters,
			const type::Type & type)
			: Expression{type}
			, function_ptr(std::move(function_ptr))
			, parameters(std::move(parameters)) {}
		virtual ~Invoke() = default;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->parameters) {
				count = std::max(elem->alloc(), count);
			}
			return std::max(count, function_ptr->alloc());
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> function_ptr;
		std::vector<std::unique_ptr<Expression>> parameters;
	};



	struct InitStruct final : public Expression {
		InitStruct() : Expression{type::Any{}} {}

		struct Member {
			std::uint64_t addr;
			std::unique_ptr<Expression> expr;
		};

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->members) {
				count = std::max(elem.expr->alloc(), count);
			}
			return count;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::vector<Member> members;
	};



	struct Choose final : Expression {
		Choose(const type::Type & type) 
			: Expression{type} {}

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & [c4se, expr] : this->cases) {
				count = std::max({c4se->alloc(), expr->alloc(), count});
			}
			return count;
		}

		virtual void accept(const ExprVisitor & visitor) const override {
			visitor.visit(*this);
		}

		std::unique_ptr<Expression> condition;

		std::vector<std::pair<
			std::unique_ptr<Expression>,
			std::unique_ptr<Expression>
		>> cases;

		std::unique_ptr<Expression> d3fault;
	};



	auto visit_expression(const sst::Expression & expr, auto && fx) {

		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, Binary>;
		using Base = FunctionVisitor<ExprVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 

			virtual void visit(const Binary & x) const override { this->run(x); };
			virtual void visit(const Unary & x) const override { this->run(x); };
			virtual void visit(const Integer & x) const override { this->run(x); };
			virtual void visit(const Float & x) const override { this->run(x); };
			virtual void visit(const Bool & x) const override { this->run(x); };
			virtual void visit(const Char & x) const override { this->run(x); };
			virtual void visit(const Null & x) const override { this->run(x); };
			virtual void visit(const String & x) const override { this->run(x); };
			virtual void visit(const Array & x) const override { this->run(x); };
			virtual void visit(const Tuple & x) const override { this->run(x); };
			virtual void visit(const Call & x) const override { this->run(x); };
			virtual void visit(const Invoke & x) const override { this->run(x); };
			virtual void visit(const Var & x) const override { this->run(x); };
			virtual void visit(const Index & x) const override { this->run(x); };
			virtual void visit(const Lambda & x) const override { this->run(x); };
			virtual void visit(const FxPointer & x) const override { this->run(x); };
			virtual void visit(const Member & x) const override { this->run(x); };
			virtual void visit(const GlobalVar & x) const override { this->run(x); };
			virtual void visit(const Iife & x) const override { this->run(x); };
			virtual void visit(const Ternary & x) const override { this->run(x); };
			virtual void visit(const Choose & x) const override { this->run(x); };
			virtual void visit(const TypedUnary & x) const override { this->run(x); };
			virtual void visit(const Reflect & x) const override { this->run(x); };
			virtual void visit(const InitStruct & x) const override { this->run(x); };
		};

		return Visitor{fx}(expr);
	}
}