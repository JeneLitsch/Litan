#pragma once
#include <vector>
#include <bitset>
#include "ltn/casts.hxx"
#include "Node.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Operations.hxx"
#include "Expression.hxx"


namespace ltn::c::sst {
	struct Assignable;
	class Statement;



	struct Ternary : public Expression {
		Ternary(
			const type::Type & type,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_branch,
			std::unique_ptr<Expression> else_branch) 
			: Expression(type)
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}
		virtual ~Ternary() = default;
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_branch;
		std::unique_ptr<Expression> else_branch;

		virtual std::uint64_t alloc() const override {
			return std::max({
				condition->alloc(),
				if_branch->alloc(),
				else_branch->alloc(),
			});
		}
	};




	struct Unary : public Expression {
		using Op = UnaryOp;
		Unary(
			Op op,
			std::unique_ptr<Expression> expression,
			const type::Type & type)
			: Expression(type)
			, op(op)
			, expression(std::move(expression)) {}
		virtual ~Unary() = default;
		Op op;
		std::unique_ptr<Expression> expression;
		virtual std::uint64_t alloc() const override {
			return this->expression->alloc();
		}
	};



	struct Binary : public Expression {
		using Op = BinaryOp;
		Binary(
			Op op,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const type::Type & type)
			: Expression(type)
			, op(op)
			, l(std::move(l))
			, r(std::move(r)) {}
		virtual ~Binary() = default;
		Op op;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
		virtual std::uint64_t alloc() const override {
			return std::max({
				l->alloc(),
				r->alloc(),
			});
		}
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
			: Expression(type)
			, query{std::move(query)}
			, addr{addr} {}
		virtual ~Reflect() = default;
		Query query;
		Addr addr;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
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
		virtual ~TypedUnary() = default;
		Op op;
		type::Type target_type;
		std::unique_ptr<Expression> expr;
		virtual std::uint64_t alloc() const override {
			return this->expr->alloc();
		}
	};


	struct Functional;
	struct Var;
	struct Assignable;
	class Statement;

	struct Primary : public Expression {
		Primary(const type::Type & type)
			: Expression(type) {}
		virtual ~Primary() = default;
	};
	

	struct Literal : public Primary {
		Literal(const type::Type & type)
			: Primary(type) {}
		virtual ~Literal() = default;
	};



	struct Integer final : public Literal {
		Integer(std::bitset<64> value, const type::Type & type)
			: Integer(static_cast<std::int64_t>(value.to_ullong()), type) {}

		Integer(std::int64_t value, const type::Type & type)
			: Literal(type)
			, value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Float final : public Literal {
		Float(stx::float64_t value, const type::Type & type)
			: Literal(type)
			, value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Bool final : public Literal {
		Bool(bool value, const type::Type & type)
			: Literal(type)
			, value(value) {}
		virtual ~Bool() = default;
		bool value;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Null final : public Literal {
		Null(const type::Type & type)
			: Literal(type) {}
		virtual ~Null() = default;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Char final : public Literal {
		Char(std::uint8_t value, const type::Type & type)
			: Literal(type)
			, value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct String final : public Literal {
		String(const std::string & value, const type::Type & type)
			: Literal(type)
			, value(value) {}
		virtual ~String() = default;
		std::string value;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Array final: public Literal {
		Array(const type::Type & type) : Literal(type) {}
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> elements;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->elements) {
				count = std::max(elem->alloc(), count);
			}
			return count;
		}
	};


	
	struct Tuple final: public Literal {
		Tuple(const type::Type & type) : Literal(type) {}
		virtual ~Tuple() = default;
		std::vector<std::unique_ptr<Expression>> elements;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->elements) {
				count = std::max(elem->alloc(), count);
			}
			return count;
		}
	};



	struct Lambda final : public Literal {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const type::Type & type)
			: Literal(type)
			, fx(std::move(fx))
			, captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};







	
	struct Assignable : public Primary {
		virtual ~Assignable() = default;
		Assignable(const type::Type & type) : Primary(type) {}
	};



	struct Index final : public Assignable {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const type::Type & type)
			: Assignable(type)
			, expression(std::move(expression))
			, index(std::move(index)) {}
		virtual ~Index() = default;
		std::unique_ptr<Expression> expression;
		std::unique_ptr<Expression> index;

		virtual std::uint64_t alloc() const override {
			return std::max({
				this->expression->alloc(),
				this->index->alloc(),
			});
		}
	};



	struct Var final : public Assignable {
	public:
		Var(
			std::size_t addr,
			const type::Type & type)
			: Assignable(type)
			, addr{addr} {}

		virtual ~Var() = default;
		std::size_t addr;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct GlobalVar final : public Assignable {
	public:
		GlobalVar(
			const type::Type & type,
			std::size_t addr)
			: Assignable(type)
			, addr { addr } {}
		virtual ~GlobalVar() = default;
		std::size_t addr;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Member final : public Assignable {
		Member(
			const type::Type & type,
			std::unique_ptr<Expression> expr,
			std::size_t addr)
			: Assignable(type)
			, expr(std::move(expr))
			, addr { addr } {};
		virtual ~Member() = default;
		std::unique_ptr<Expression> expr;
		std::size_t addr;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Iife final : public Primary {
		Iife(
			const type::Type & type,
			std::string return_label,
			std::unique_ptr<Statement> stmt,
			type::Type return_type) 
			: Primary(type)
			, return_label{return_label}
			, stmt(std::move(stmt))
			, return_type{return_type} {}
		virtual ~Iife() = default;

		std::string return_label;
		std::unique_ptr<Statement> stmt;
		type::Type return_type;

		virtual std::uint64_t alloc() const override {
			return this->stmt->direct_alloc() + this->stmt->nested_alloc();
		}
	};



	struct FxPointer final : public Primary {
	public:
		FxPointer(
			const Label & label,
			std::size_t arity,
			const type::Type & type)
			: Primary(type)
			, label{label}
			, arity{arity} {}
		virtual ~FxPointer() = default;
		Label label;
		std::size_t arity;

		virtual std::uint64_t alloc() const override {
			return 0;
		}
	};



	struct Call final : public Primary {
	public:
		Call(
			const Label & label,
			std::vector<std::unique_ptr<Expression>> parameters,
			const type::Type & type)
			: Primary(type)
			, label{label}
			, parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		Label label;
		std::vector<std::unique_ptr<Expression>> parameters;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->parameters) {
				count = std::max(elem->alloc(), count);
			}
			return count;
		}
	};


	struct Invoke final : public Primary {
	public:
		Invoke(
			std::unique_ptr<Expression> function_ptr,
			std::vector<std::unique_ptr<Expression>> parameters,
			const type::Type & type)
			: Primary(type)
			, function_ptr(std::move(function_ptr))
			, parameters(std::move(parameters)) {}
		virtual ~Invoke() = default;
		std::unique_ptr<Expression> function_ptr;
		std::vector<std::unique_ptr<Expression>> parameters;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->parameters) {
				count = std::max(elem->alloc(), count);
			}
			return std::max(count, function_ptr->alloc());
		}
	};



	struct InitStruct final : public Expression {
		InitStruct() : Expression{type::Any{}} {}
		virtual ~InitStruct() = default;
		struct Member {
			std::uint64_t addr;
			std::unique_ptr<Expression> expr;
		};
		std::vector<Member> members;

		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & elem : this->members) {
				count = std::max(elem.expr->alloc(), count);
			}
			return count;
		}
	};




	struct ExprSwitch : Switch<Primary, Expression> {
		ExprSwitch(const type::Type & type) : Switch<Primary, Expression>{type} {}
		virtual std::uint64_t alloc() const override {
			std::uint64_t count = 0;
			for(const auto & [c4se, expr] : this->cases) {
				count = std::max({c4se->alloc(), expr->alloc(), count});
			}
			return count;
		}
	};



	auto visit_expression(const sst::Expression & expr, auto && fx) {
		if(auto e = as<sst::Binary>(expr)) return fx(*e);
		if(auto e = as<sst::Unary>(expr)) return fx(*e);
		if(auto e = as<sst::Integer>(expr)) return fx(*e);
		if(auto e = as<sst::Float>(expr)) return fx(*e);
		if(auto e = as<sst::Bool>(expr)) return fx(*e);
		if(auto e = as<sst::Char>(expr)) return fx(*e);
		if(auto e = as<sst::Null>(expr)) return fx(*e);
		if(auto e = as<sst::String>(expr)) return fx(*e);
		if(auto e = as<sst::Array>(expr)) return fx(*e);
		if(auto e = as<sst::Tuple>(expr)) return fx(*e);
		if(auto e = as<sst::Call>(expr)) return fx(*e);
		if(auto e = as<sst::Invoke>(expr)) return fx(*e);
		if(auto e = as<sst::Var>(expr)) return fx(*e);
		if(auto e = as<sst::Index>(expr)) return fx(*e);
		if(auto e = as<sst::Lambda>(expr)) return fx(*e);
		if(auto e = as<sst::FxPointer>(expr)) return fx(*e);
		if(auto e = as<sst::Member>(expr)) return fx(*e);
		if(auto e = as<sst::GlobalVar>(expr)) return fx(*e);
		if(auto e = as<sst::Iife>(expr)) return fx(*e);
		if(auto e = as<sst::Ternary>(expr)) return fx(*e);
		if(auto e = as<sst::ExprSwitch>(expr)) return fx(*e);
		if(auto e = as<sst::TypedUnary>(expr)) return fx(*e);
		if(auto e = as<sst::Reflect>(expr)) return fx(*e);
		if(auto e = as<sst::InitStruct>(expr)) return fx(*e);
		throw std::runtime_error{"Unknown Expression SST"};
	}
}