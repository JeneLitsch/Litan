#pragma once
#include <vector>
#include <utility>
#include <variant>
#include <bitset>
#include "ltn/casts.hxx"
#include "Switch.hxx"
#include "Node.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/Operations.hxx"
#include "Expression.hxx"

namespace ltn::c::ast {
	struct Assignable;
	class Statement;
	struct Function;







	struct ForwardDynamicCall {
		ForwardDynamicCall(
			std::uint64_t addr,
			std::uint64_t arity,
			const SourceLocation & location)
			: location{location}
			, addr{addr}
			, arity{arity} {}
		virtual ~ForwardDynamicCall() = default;
		SourceLocation location;
		std::uint64_t addr;
		std::uint64_t arity;
	};
	


	struct Ternary {
		Ternary(
			const SourceLocation & location,
			Expression condition,
			Expression if_branch,
			Expression else_branch) 
			: location{location}
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}
		virtual ~Ternary() = default;
	
		SourceLocation location;
		Expression condition;
		Expression if_branch;
		Expression else_branch;
	};




	struct Unary {
		using Op = UnaryOp;
		Unary(
			Op op,
			Expression expression,
			const SourceLocation & location)
			: location{location}
			, op(op)
			, expression(std::move(expression)) {}
		virtual ~Unary() = default;
		SourceLocation location;
		Op op;
		Expression expression;
	};



	struct Binary {
		using Op = BinaryOp;
		Binary(
			Op op,
			Expression l,
			Expression r,
			const SourceLocation & location)
			: location{location}
			, op(op)
			, l(std::move(l))
			, r(std::move(r)) {}
		virtual ~Binary() = default;
		SourceLocation location;
		Op op;
		Expression l;
		Expression r;
	};



	struct Reflect {
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
			Expression expr;
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
			: location{location}
			, query{std::move(query)} {}
		virtual ~Reflect() = default;
		SourceLocation location;
		Query query;
	};



	struct TypedUnary final {
	public:
		using Op = TypedUnaryOp;
		TypedUnary(
			Op op,
			const type::IncompleteType & type,
			Expression expr,
			const SourceLocation & location)
			: location{location}
			, op{op}
			, type{type}
			, expr{std::move(expr)} {}
		virtual ~TypedUnary() = default;
		SourceLocation location;
		Op op;
		type::IncompleteType type;
		Expression expr;
	};


	struct Functional;
	struct Var;
	struct Assignable;
	class Statement;

	struct Integer final {
		Integer(std::bitset<64> value, const SourceLocation & location)
			: Integer(static_cast<std::int64_t>(value.to_ullong()), location) {}

		Integer(std::int64_t value, const SourceLocation & location)
			: location{location}, value(value) {}
		virtual ~Integer() = default;
		SourceLocation location;
		std::int64_t value;
	};



	struct Float final {
		Float(stx::float64_t value, const SourceLocation & location)
			: location{location}, value(value) {}
		virtual ~Float() = default;
		SourceLocation location;
		stx::float64_t value;
	};



	struct Bool final {
		Bool(bool value, const SourceLocation & location)
			: location{location}, value(value) {}
		virtual ~Bool() = default;
		SourceLocation location;
		bool value;
	};



	struct Null final {
		Null(const SourceLocation & location)
			: location{location} {}
		virtual ~Null() = default;
		SourceLocation location;
	};



	struct Char final {
		Char(std::uint8_t value, const SourceLocation & location)
			: location{location}, value(value) {}
		virtual ~Char() = default;
		SourceLocation location;
		std::uint8_t value;
	};



	struct String final {
		String(const std::string & value, const SourceLocation & location)
			: location{location}, value(value) {}
		virtual ~String() = default;
		SourceLocation location;
		std::string value;
	};



	struct Array final{
		Array(
			const SourceLocation & location,
			std::vector<Expression> elements)
			: location{location}
			, elements{std::move(elements)} {}

		SourceLocation location;
		std::vector<Expression> elements;
	};



	struct Tuple final{
		Tuple(
			const SourceLocation & location,
			std::vector<Expression> elements)
			: location{location}
			, elements{std::move(elements)} {}
		virtual ~Tuple() = default;
		SourceLocation location;
		std::vector<Expression> elements;
	};



	struct Lambda final {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const SourceLocation & location)
			: location{location}
			, fx(std::move(fx))
			, captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		SourceLocation location;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};


	
	struct Index final {
		Index(
			Expression expression,
			Expression index,
			const SourceLocation & location)
			: location{location}
			, expression(std::move(expression))
			, index(std::move(index)) {}
		virtual ~Index() = default;
		SourceLocation location;
		Expression expression;
		Expression index;
	};



	struct Var final {
		Var(
			const std::string & name,
			const Namespace & namespaze,
			const SourceLocation & location)
			: location{location}
			, name{name}
			, namespaze{namespaze} {}

		virtual ~Var() = default;
		SourceLocation location;
		std::string name;
		Namespace namespaze;
	};



	struct GlobalVar final {
		GlobalVar(
			const SourceLocation & location,
			const Namespace & namespaze,
			const std::string & name)
			: location{location}
			, name { name }
			, namespaze { namespaze } {}
		virtual ~GlobalVar() = default;
		SourceLocation location;
		std::string name;
		Namespace namespaze;
	};



	struct Member final {
		Member(
			Expression expr,
			const std::string & name,
			const SourceLocation & location)
			: location{location}
			, expr(std::move(expr))
			, name(std::move(name)){};
		virtual ~Member() = default;
		SourceLocation location;
		Expression expr;
		std::string name;
	};



	struct Iife final {
		Iife(
			const SourceLocation & location,
			std::unique_ptr<Statement> stmt,
			type::IncompleteType return_type) 
			: location{location}
			, stmt(std::move(stmt))
			, return_type{return_type} {}
		virtual ~Iife() = default;
		
		SourceLocation location;
		std::unique_ptr<Statement> stmt;
		type::IncompleteType return_type;
	};



	struct FxPointer final {
		FxPointer(
			const std::string & name,
			const Namespace & namespaze,
			const std::size_t placeholders,
			const SourceLocation & location)
			: location{location}
			, name(name)
			, namespaze(namespaze)
			, placeholders(std::move(placeholders)) {}
		virtual ~FxPointer() = default;
		SourceLocation location;
		std::string name;
		Namespace namespaze;
		std::size_t placeholders;
		std::vector<type::IncompleteType> template_arguements;
	};



	struct Call final {
		Call(
			Expression function_ptr,
			std::vector<Expression> parameters,
			const SourceLocation & location)
			: location{location}
			, function_ptr(std::move(function_ptr))
			, parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		SourceLocation location;
		Expression function_ptr;
		std::vector<Expression> parameters;
		std::vector<type::IncompleteType> template_args;
	};



	struct InitStruct final {
		InitStruct(const SourceLocation & location)
			: location{location} {}
		virtual ~InitStruct() = default;
		SourceLocation location;
		struct Member {
			std::string name;
			Expression expr;
		};
		std::vector<Member> members;
	};


	struct ExprSwitch {
		ExprSwitch(const SourceLocation & location) : location{location} {}
		SourceLocation location;
		Expression condition;
		std::vector<std::pair<
			Expression,
			Expression
		>> cases;
		Expression d3fault;
	};




	decltype(auto) visit_expression(const ast::Expression & expr, auto && fx) {
		if(!expr) {
			throw std::runtime_error{"Empty ExprBase AST"};
		}
		if(auto e = expr.as<ast::Binary>()) return fx(*e);
		if(auto e = expr.as<ast::Unary>()) return fx(*e);
		if(auto e = expr.as<ast::Integer>()) return fx(*e);
		if(auto e = expr.as<ast::Float>()) return fx(*e);
		if(auto e = expr.as<ast::Bool>()) return fx(*e);
		if(auto e = expr.as<ast::Char>()) return fx(*e);
		if(auto e = expr.as<ast::Null>()) return fx(*e);
		if(auto e = expr.as<ast::String>()) return fx(*e);
		if(auto e = expr.as<ast::Array>()) return fx(*e);
		if(auto e = expr.as<ast::Tuple>()) return fx(*e);
		if(auto e = expr.as<ast::Call>()) return fx(*e);
		if(auto e = expr.as<ast::Var>()) return fx(*e);
		if(auto e = expr.as<ast::Index>()) return fx(*e);
		if(auto e = expr.as<ast::Lambda>()) return fx(*e);
		if(auto e = expr.as<ast::FxPointer>()) return fx(*e);
		if(auto e = expr.as<ast::Member>()) return fx(*e);
		if(auto e = expr.as<ast::GlobalVar>()) return fx(*e);
		if(auto e = expr.as<ast::Iife>()) return fx(*e);
		if(auto e = expr.as<ast::Ternary>()) return fx(*e);
		if(auto e = expr.as<ast::ExprSwitch>()) return fx(*e);
		if(auto e = expr.as<ast::TypedUnary>()) return fx(*e);
		if(auto e = expr.as<ast::Reflect>()) return fx(*e);
		if(auto e = expr.as<ast::ForwardDynamicCall>()) return fx(*e);
		if(auto e = expr.as<ast::InitStruct>()) return fx(*e);
		throw std::runtime_error{"Unknown ExprBase AST"};
	}


	inline const SourceLocation & location(const ast::Expression & expr) {
		return visit_expression(expr, [&] (const auto & e) -> const SourceLocation & {
			return e.location;
		});
	}
}