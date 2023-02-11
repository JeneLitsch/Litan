#pragma once
#include <vector>
#include <utility>
#include <bitset>
#include "ltn/casts.hxx"
#include "Switch.hxx"
#include "Node.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Operations.hxx"


namespace ltn::c::ast {
	struct Assignable;
	class Statement;
	struct Function;



	struct Expression : public Node {
		Expression(const SourceLocation & location) : Node(location) {}
		virtual ~Expression() = default;
	};



	struct ForwardDynamicCall : public Expression {
		ForwardDynamicCall(
			std::uint64_t addr,
			std::uint64_t arity,
			const SourceLocation & location)
			: Expression(location)
			, addr{addr}
			, arity{arity} {}
		virtual ~ForwardDynamicCall() = default;
		std::uint64_t addr;
		std::uint64_t arity;
	};
	


	struct Ternary : public Expression {
		Ternary(
			const SourceLocation & location,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_branch,
			std::unique_ptr<Expression> else_branch) 
			: Expression(location)
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}
		virtual ~Ternary() = default;
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_branch;
		std::unique_ptr<Expression> else_branch;
	};




	struct Unary : public Expression {
		using Op = UnaryOp;
		Unary(
			Op op,
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			: Expression(location)
			, op(op)
			, expression(std::move(expression)) {}
		virtual ~Unary() = default;
		Op op;
		std::unique_ptr<Expression> expression;
	};



	struct Binary : public Expression {
		using Op = BinaryOp;
		Binary(
			Op op,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			: Expression(location)
			, op(op)
			, l(std::move(l))
			, r(std::move(r)) {}
		virtual ~Binary() = default;
		Op op;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};



	struct Reflect : public Expression {
		struct NamespaceQuery {
			Namespace namespaze;
		};
		struct FunctionQuery {
			Namespace namespaze;
			std::string name;
			std::size_t arity;
		};
		struct FileQuery {};
		struct LineQuery {};
		struct LocationQuery {
			FileQuery file;
			LineQuery line;
		};
		struct ExprQuery {
			std::unique_ptr<Expression> expr;
		};
		struct TypeQuery {
			type::IncompleteType type;
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
		Reflect(
			Query query,
			const SourceLocation & location)
			: Expression(location)
			, query{std::move(query)} {}
		virtual ~Reflect() = default;
		Query query;
	};



	struct TypedUnary final : public Expression {
	public:
		using Op = TypedUnaryOp;
		TypedUnary(
			Op op,
			const type::IncompleteType & type,
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			: Expression{location}
			, op{op}
			, type{type}
			, expr{std::move(expr)} {}
		virtual ~TypedUnary() = default;
		Op op;
		type::IncompleteType type;
		std::unique_ptr<Expression> expr;
	};


	struct Functional;
	struct Var;
	struct Assignable;
	class Statement;

	struct Integer final : public Expression {
		Integer(std::bitset<64> value, const SourceLocation & location)
			: Integer(static_cast<std::int64_t>(value.to_ullong()), location) {}

		Integer(std::int64_t value, const SourceLocation & location)
			: Expression(location), value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};



	struct Float final : public Expression {
		Float(stx::float64_t value, const SourceLocation & location)
			: Expression(location), value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;
	};



	struct Bool final : public Expression {
		Bool(bool value, const SourceLocation & location)
			: Expression(location), value(value) {}
		virtual ~Bool() = default;
		bool value;
	};



	struct Null final : public Expression {
		Null(const SourceLocation & location)
			: Expression(location) {}
		virtual ~Null() = default;
	};



	struct Char final : public Expression {
		Char(std::uint8_t value, const SourceLocation & location)
			: Expression(location), value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;
	};



	struct String final : public Expression {
		String(const std::string & value, const SourceLocation & location)
			: Expression(location), value(value) {}
		virtual ~String() = default;
		std::string value;
	};



	struct Array final: public Expression {
		Array(
			const SourceLocation & location,
			std::vector<std::unique_ptr<Expression>> elements)
			: Expression(location)
			, elements{std::move(elements)} {}
		
		virtual ~Array() = default;
		std::vector<std::unique_ptr<Expression>> elements;
	};



	struct Tuple final: public Expression {
		Tuple(
			const SourceLocation & location,
			std::vector<std::unique_ptr<Expression>> elements)
			: Expression(location)
			, elements{std::move(elements)} {}
		virtual ~Tuple() = default;
		std::vector<std::unique_ptr<Expression>> elements;
	};



	struct Lambda final : public Expression {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const SourceLocation & location)
			: Expression(location)
			, fx(std::move(fx))
			, captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};


	
	struct Index final : public Expression {
		Index(
			std::unique_ptr<Expression> expression,
			std::unique_ptr<Expression> index,
			const SourceLocation & location)
			: Expression(location)
			, expression(std::move(expression))
			, index(std::move(index)) {}
		virtual ~Index() = default;
		std::unique_ptr<Expression> expression;
		std::unique_ptr<Expression> index;
	};



	struct Var final : public Expression {
		Var(
			const std::string & name,
			const Namespace & namespaze,
			const SourceLocation & location)
			: Expression(location)
			, name{name}
			, namespaze{namespaze} {}

		virtual ~Var() = default;
		std::string name;
		Namespace namespaze;
	};



	struct GlobalVar final : public Expression {
		GlobalVar(
			const SourceLocation & location,
			const Namespace & namespaze,
			const std::string & name)
			: Expression(location)
			, name { name }
			, namespaze { namespaze } {}
		virtual ~GlobalVar() = default;
		std::string name;
		Namespace namespaze;
	};



	struct Member final : public Expression {
		Member(
			std::unique_ptr<Expression> expr,
			const std::string & name,
			const SourceLocation & location)
			: Expression(location)
			, expr(std::move(expr))
			, name(std::move(name)){};
		virtual ~Member() = default;
		std::unique_ptr<Expression> expr;
		std::string name;
	};



	struct Iife final : public Expression {
		Iife(
			const SourceLocation & location,
			std::unique_ptr<Statement> stmt,
			type::IncompleteType return_type) 
			: Expression(location)
			, stmt(std::move(stmt))
			, return_type{return_type} {}
		virtual ~Iife() = default;
		
		std::unique_ptr<Statement> stmt;
		type::IncompleteType return_type;
	};



	struct FxPointer final : public Expression {
		FxPointer(
			const std::string & name,
			const Namespace & namespaze,
			const std::size_t placeholders,
			const SourceLocation & location)
			: Expression(location)
			, name(name)
			, namespaze(namespaze)
			, placeholders(std::move(placeholders)) {}
		virtual ~FxPointer() = default;
		std::string name;
		Namespace namespaze;
		std::size_t placeholders;
		std::vector<type::IncompleteType> template_arguements;
	};



	struct Call final : public Expression {
		Call(
			std::unique_ptr<Expression> function_ptr,
			std::vector<std::unique_ptr<Expression>> parameters,
			const SourceLocation & location)
			: Expression(location)
			, function_ptr(std::move(function_ptr))
			, parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		std::unique_ptr<Expression> function_ptr;
		std::vector<std::unique_ptr<Expression>> parameters;
		std::vector<type::IncompleteType> template_args;
	};



	struct InitStruct final : public Expression {
		InitStruct(const SourceLocation & location)
			: Expression{location} {}
		virtual ~InitStruct() = default;
		struct Member {
			std::string name;
			std::unique_ptr<Expression> expr;
		};
		std::vector<Member> members;
	};



	using ExprSwitch = Switch<Expression>;



	auto visit_expression(const ast::Expression & expr, auto && fx) {
		if(auto e = as<ast::Binary>(expr)) return fx(*e);
		if(auto e = as<ast::Unary>(expr)) return fx(*e);
		if(auto e = as<ast::Integer>(expr)) return fx(*e);
		if(auto e = as<ast::Float>(expr)) return fx(*e);
		if(auto e = as<ast::Bool>(expr)) return fx(*e);
		if(auto e = as<ast::Char>(expr)) return fx(*e);
		if(auto e = as<ast::Null>(expr)) return fx(*e);
		if(auto e = as<ast::String>(expr)) return fx(*e);
		if(auto e = as<ast::Array>(expr)) return fx(*e);
		if(auto e = as<ast::Tuple>(expr)) return fx(*e);
		if(auto e = as<ast::Call>(expr)) return fx(*e);
		if(auto e = as<ast::Var>(expr)) return fx(*e);
		if(auto e = as<ast::Index>(expr)) return fx(*e);
		if(auto e = as<ast::Lambda>(expr)) return fx(*e);
		if(auto e = as<ast::FxPointer>(expr)) return fx(*e);
		if(auto e = as<ast::Member>(expr)) return fx(*e);
		if(auto e = as<ast::GlobalVar>(expr)) return fx(*e);
		if(auto e = as<ast::Iife>(expr)) return fx(*e);
		if(auto e = as<ast::Ternary>(expr)) return fx(*e);
		if(auto e = as<ast::ExprSwitch>(expr)) return fx(*e);
		if(auto e = as<ast::TypedUnary>(expr)) return fx(*e);
		if(auto e = as<ast::Reflect>(expr)) return fx(*e);
		if(auto e = as<ast::ForwardDynamicCall>(expr)) return fx(*e);
		if(auto e = as<ast::InitStruct>(expr)) return fx(*e);
		throw std::runtime_error{"Unknown Expression AST"};
	}
}