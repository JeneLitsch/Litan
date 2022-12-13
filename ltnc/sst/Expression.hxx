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
		Expression(const SourceLocation & location) : Node(location) {}
		virtual ~Expression() = default;
	};
	


	struct DeclType : public Expression {
		DeclType(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Expression(location),
				expression(std::move(expression)) {}
		virtual ~DeclType() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Ternary : public Expression {
		Ternary(
			const SourceLocation & location,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_branch,
			std::unique_ptr<Expression> else_branch) 
			:	Expression(location),
				condition(std::move(condition)),
				if_branch(std::move(if_branch)),
				else_branch(std::move(else_branch)) {}
		virtual ~Ternary() = default;
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_branch;
		std::unique_ptr<Expression> else_branch;
	};




	struct Unary : public Expression {
		enum class Type { NEG, NOT, NUL, BITNOT, DEREF };
		Unary(
			Type type,
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Expression(location),
				type(type),
				expression(std::move(expression)) {}
		virtual ~Unary() = default;
		Type type;
		std::unique_ptr<Expression> expression;
	};



	struct Binary : public Expression {
		enum class Type {
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
			Type type,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Expression(location),
				type(type),
				l(std::move(l)),
				r(std::move(r)) {}
		virtual ~Binary() = default;
		Type type;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};



	struct Reflect : public Expression {
		Reflect(
			const ReflectQuery & query,
			const SourceLocation & location)
			:	Expression(location),
				query{query} {}
		virtual ~Reflect() = default;
		ReflectQuery query;
	};



	struct TypedUnary final : public Expression {
	public:
		enum class Op {
			STATIC_CAST, DYNAMIC_CAST,
			STATIC_COPY, DYNAMIC_COPY
		};
		TypedUnary(
			Op op,
			const type::IncompleteType & type,
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			:	Expression{location},
				op{op},
				type{type},
				expr{std::move(expr)} {}
		virtual ~TypedUnary() = default;
		Op op;
		type::IncompleteType type;
		std::unique_ptr<Expression> expr;
	};


	struct Functional;
	struct Var;
	struct Assignable;
	struct Statement;

	struct Primary : public Expression {
		Primary(const SourceLocation & location) : Expression(location) {}
		virtual ~Primary() = default;
	};
	

	struct Literal : public Primary {
		Literal(const SourceLocation & location)
			:	Primary(location) {}
		virtual ~Literal() = default;
	};



	struct Integer final : public Literal {
		Integer(std::bitset<64> value, const SourceLocation & location)
			:	Integer(static_cast<std::int64_t>(value.to_ullong()), location) {}

		Integer(std::int64_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};



	struct Float final : public Literal {
		Float(stx::float64_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;
	};



	struct Bool final : public Literal {
		Bool(bool value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Bool() = default;
		bool value;
	};



	struct Null final : public Literal {
		Null(const SourceLocation & location)
			:	Literal(location) {}
		virtual ~Null() = default;
	};



	struct Char final : public Literal {
		Char(std::uint8_t value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;
	};



	struct String final : public Literal {
		String(const std::string & value, const SourceLocation & location)
			:	Literal(location), value(value) {}
		virtual ~String() = default;
		std::string value;
	};



	struct Array final: public Literal {
		Array(const SourceLocation & location) : Literal(location) {}
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> elements;
	};



	struct Lambda final : public Literal {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const SourceLocation & location)
			:	Literal(location),
				fx(std::move(fx)),
				captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};







	
	struct Assignable : public Primary {
		virtual ~Assignable() = default;
		Assignable(const SourceLocation & location) : Primary(location) {}
	};



	struct Index final : public Assignable {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const SourceLocation & location)
			:	Assignable(location),
				expression(std::move(expression)),
				index(std::move(index)) {}
		virtual ~Index() = default;
		std::unique_ptr<Expression> expression;
		std::unique_ptr<Expression> index;
	};



	struct Var final : public Assignable {
	public:
		Var(
			const std::string & name,
			const Namespace & namespaze,
			const SourceLocation & location)
			:	Assignable(location),
				name{name},
				namespaze{namespaze} {}

		virtual ~Var() = default;
		std::string name;
		Namespace namespaze;
	};



	struct GlobalVar final : public Assignable {
	public:
		GlobalVar(
			const SourceLocation & location,
			const Namespace & namespaze,
			const std::string & name) :
				Assignable(location),
				name { name },
				namespaze { namespaze } {}
		virtual ~GlobalVar() = default;
		std::string name;
		Namespace namespaze;
	};



	struct Member final : public Assignable {
		Member(
			std::unique_ptr<Expression> expr,
			const std::string & name,
			const SourceLocation & location)
			:	Assignable(location),
				expr(std::move(expr)),
				name(std::move(name)){};
		virtual ~Member() = default;
		std::unique_ptr<Expression> expr;
		std::string name;
	};



	struct Iife final : public Primary {
		Iife(
			const SourceLocation & location,
			std::unique_ptr<Statement> stmt,
			type::IncompleteType return_type) 
			:	Primary(location), 
				stmt(std::move(stmt)),
				return_type{return_type} {}
		virtual ~Iife() = default;
		
		std::unique_ptr<Statement> stmt;
		type::IncompleteType return_type;
	};



	struct FxPointer final : public Primary {
	public:
		FxPointer(
			const std::string & name,
			const Namespace & namespaze,
			const std::size_t placeholders,
			const SourceLocation & location)
			:	Primary(location),
				name(name),
				namespaze(namespaze),
				placeholders(std::move(placeholders)) {}
		virtual ~FxPointer() = default;
		std::string name;
		Namespace namespaze;
		std::size_t placeholders;
		std::vector<type::IncompleteType> template_arguements;
	};



	struct Call final : public Primary {
	public:
		Call(
			std::unique_ptr<Expression> function_ptr,
			std::vector<std::unique_ptr<Expression>> parameters,
			const SourceLocation & location)
			:	Primary(location),
				function_ptr(std::move(function_ptr)),
				parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		std::unique_ptr<Expression> function_ptr;
		std::vector<std::unique_ptr<Expression>> parameters;
		std::vector<type::IncompleteType> template_args;
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
		throw std::runtime_error{"Unknown Expression"};
	}
}