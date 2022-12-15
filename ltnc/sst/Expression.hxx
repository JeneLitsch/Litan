#pragma once
#include <vector>
#include <bitset>
#include "ltn/casts.hxx"
#include "Node.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/ReflectQuery.hxx"


namespace ltn::c::sst {
	struct Assignable;
	struct Statement;



	struct Expression : public Node {
		Expression(const type::Type & type) : type{type} {}
		virtual ~Expression() = default;
		type::Type type;
	};
	using expr_ptr = std::unique_ptr<Expression>;
	


	struct DeclType : public Expression {
		DeclType(
			std::size_t name_addr,
			std::unique_ptr<Expression> expression,
			const type::Type & type)
			:	Expression(type),
				name_addr{name_addr},
				expression(std::move(expression)) {}
		virtual ~DeclType() = default;
		std::size_t name_addr;
		std::unique_ptr<Expression> expression;
	};



	struct Ternary : public Expression {
		Ternary(
			const type::Type & type,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_branch,
			std::unique_ptr<Expression> else_branch) 
			:	Expression(type),
				condition(std::move(condition)),
				if_branch(std::move(if_branch)),
				else_branch(std::move(else_branch)) {}
		virtual ~Ternary() = default;
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_branch;
		std::unique_ptr<Expression> else_branch;
	};




	struct Unary : public Expression {
		enum class Op { NEG, NOT, NUL, BITNOT, DEREF };
		Unary(
			Op op,
			std::unique_ptr<Expression> expression,
			const type::Type & type)
			:	Expression(type),
				op(op),
				expression(std::move(expression)) {}
		virtual ~Unary() = default;
		Op op;
		std::unique_ptr<Expression> expression;
	};



	struct Binary : public Expression {
		enum class Op {
			ADD, SUB,
			MLT, DIV, MOD, POW,
			BIGGER, SMALLER, BIGGEREQUAL, SMALLEREQUAL,
			EQUAL, UNEQUEL,
			SPACE_SHIP,
			SHIFT_L, SHIFT_R,
			AND, OR,
			NULLCO, ELVIS,
			BIT_OR, BIT_AND, BIT_XOR,
		};
		Binary(
			Op op,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const type::Type & type)
			:	Expression(type),
				op(op),
				l(std::move(l)),
				r(std::move(r)) {}
		virtual ~Binary() = default;
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
		using Query = std::variant<
			NamespaceQuery,
			FunctionQuery
		>;
		struct Addr {
			std::size_t name;
			std::uint64_t full_name;
			std::uint64_t fx_ptr;
			std::uint64_t functions;
			std::uint64_t c0nst; 
			std::uint64_t pr1vate; 
			std::uint64_t ext3rn; 
		};

		Reflect(
			const Query & query,
			Addr addr,
			const type::Type & type)
			:	Expression(type),
				query{query},
				addr{addr} {}
		virtual ~Reflect() = default;
		Query query;
		Addr addr;
	};



	struct TypedUnary final : public Expression {
	public:
		enum class Op {
			STATIC_CAST, DYNAMIC_CAST,
			STATIC_COPY, DYNAMIC_COPY
		};
		TypedUnary(
			Op op,
			const type::Type & target_type,
			std::unique_ptr<Expression> expr,
			const type::Type & type)
			:	Expression{type},
				op{op},
				target_type{target_type},
				expr{std::move(expr)} {}
		virtual ~TypedUnary() = default;
		Op op;
		type::Type target_type;
		std::unique_ptr<Expression> expr;
	};


	struct Functional;
	struct Var;
	struct Assignable;
	struct Statement;

	struct Primary : public Expression {
		Primary(const type::Type & type) : Expression(type) {}
		virtual ~Primary() = default;
	};
	

	struct Literal : public Primary {
		Literal(const type::Type & type)
			:	Primary(type) {}
		virtual ~Literal() = default;
	};



	struct Integer final : public Literal {
		Integer(std::bitset<64> value, const type::Type & type)
			:	Integer(static_cast<std::int64_t>(value.to_ullong()), type) {}

		Integer(std::int64_t value, const type::Type & type)
			:	Literal(type), value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};



	struct Float final : public Literal {
		Float(stx::float64_t value, const type::Type & type)
			:	Literal(type), value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;
	};



	struct Bool final : public Literal {
		Bool(bool value, const type::Type & type)
			:	Literal(type), value(value) {}
		virtual ~Bool() = default;
		bool value;
	};



	struct Null final : public Literal {
		Null(const type::Type & type)
			:	Literal(type) {}
		virtual ~Null() = default;
	};



	struct Char final : public Literal {
		Char(std::uint8_t value, const type::Type & type)
			:	Literal(type), value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;
	};



	struct String final : public Literal {
		String(const std::string & value, const type::Type & type)
			:	Literal(type), value(value) {}
		virtual ~String() = default;
		std::string value;
	};



	struct Array final: public Literal {
		Array(const type::Type & type) : Literal(type) {}
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> elements;
	};



	struct Lambda final : public Literal {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const type::Type & type)
			:	Literal(type),
				fx(std::move(fx)),
				captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
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
			:	Assignable(type),
				expression(std::move(expression)),
				index(std::move(index)) {}
		virtual ~Index() = default;
		std::unique_ptr<Expression> expression;
		std::unique_ptr<Expression> index;
	};



	struct Var final : public Assignable {
	public:
		Var(
			std::size_t addr,
			const type::Type & type)
			:	Assignable(type),
				addr{addr}
				{}

		virtual ~Var() = default;
		std::size_t addr;
	};



	struct GlobalVar final : public Assignable {
	public:
		GlobalVar(
			const type::Type & type,
			std::size_t addr) :
				Assignable(type),
				addr { addr } {}
		virtual ~GlobalVar() = default;
		std::size_t addr;
	};



	struct Member final : public Assignable {
		Member(
			const type::Type & type,
			std::unique_ptr<Expression> expr,
			std::size_t addr)
			:	Assignable(type),
				expr(std::move(expr)),
				addr { addr } {};
		virtual ~Member() = default;
		std::unique_ptr<Expression> expr;
		std::size_t addr;
	};



	struct Iife final : public Primary {
		Iife(
			const type::Type & type,
			std::string return_label,
			std::unique_ptr<Statement> stmt,
			type::Type return_type) 
			:	Primary(type), 
				return_label{return_label},
				stmt(std::move(stmt)),
				return_type{return_type} {}
		virtual ~Iife() = default;

		std::string return_label;
		std::unique_ptr<Statement> stmt;
		type::Type return_type;
	};



	struct FxPointer final : public Primary {
	public:
		FxPointer(
			std::string id,
			std::size_t arity,
			const type::Type & type)
			:	Primary(type),
				id{id},
				arity{arity} {}
		virtual ~FxPointer() = default;
		std::string id;
		std::size_t arity;
	};



	struct Call final : public Primary {
	public:
		Call(
			const std::string & id,
			std::vector<std::unique_ptr<Expression>> parameters,
			const type::Type & type)
			:	Primary(type),
				id{id},
				parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		std::string id;
		std::vector<std::unique_ptr<Expression>> parameters;
	};


	struct Invoke final : public Primary {
	public:
		Invoke(
			std::unique_ptr<Expression> function_ptr,
			std::vector<std::unique_ptr<Expression>> parameters,
			const type::Type & type)
			:	Primary(type),
				function_ptr(std::move(function_ptr)),
				parameters(std::move(parameters)) {}
		virtual ~Invoke() = default;
		std::unique_ptr<Expression> function_ptr;
		std::vector<std::unique_ptr<Expression>> parameters;
	};



	using ExprSwitch = Switch<Primary, Expression>;



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
		if(auto e = as<sst::DeclType>(expr)) return fx(*e);
		if(auto e = as<sst::TypedUnary>(expr)) return fx(*e);
		if(auto e = as<sst::Reflect>(expr)) return fx(*e);
		throw std::runtime_error{"Unknown Expression SST"};
	}
}