#pragma once
#include <vector>
#include <utility>
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



	struct ExprBase : public Node {
		ExprBase(const SourceLocation & location) : Node(location) {}
		virtual ~ExprBase() = default;
	};



	struct ForwardDynamicCall : public ExprBase {
		ForwardDynamicCall(
			std::uint64_t addr,
			std::uint64_t arity,
			const SourceLocation & location)
			: ExprBase(location)
			, addr{addr}
			, arity{arity} {}
		virtual ~ForwardDynamicCall() = default;
		std::uint64_t addr;
		std::uint64_t arity;
	};
	


	struct Ternary : public ExprBase {
		Ternary(
			const SourceLocation & location,
			Expression condition,
			Expression if_branch,
			Expression else_branch) 
			: ExprBase(location)
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}
		virtual ~Ternary() = default;
	
		Expression condition;
		Expression if_branch;
		Expression else_branch;
	};




	struct Unary : public ExprBase {
		using Op = UnaryOp;
		Unary(
			Op op,
			Expression expression,
			const SourceLocation & location)
			: ExprBase(location)
			, op(op)
			, expression(std::move(expression)) {}
		virtual ~Unary() = default;
		Op op;
		Expression expression;
	};



	struct Binary : public ExprBase {
		using Op = BinaryOp;
		Binary(
			Op op,
			Expression l,
			Expression r,
			const SourceLocation & location)
			: ExprBase(location)
			, op(op)
			, l(std::move(l))
			, r(std::move(r)) {}
		virtual ~Binary() = default;
		Op op;
		Expression l;
		Expression r;
	};



	struct Reflect : public ExprBase {
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
			: ExprBase(location)
			, query{std::move(query)} {}
		virtual ~Reflect() = default;
		Query query;
	};



	struct TypedUnary final : public ExprBase {
	public:
		using Op = TypedUnaryOp;
		TypedUnary(
			Op op,
			const type::IncompleteType & type,
			Expression expr,
			const SourceLocation & location)
			: ExprBase{location}
			, op{op}
			, type{type}
			, expr{std::move(expr)} {}
		virtual ~TypedUnary() = default;
		Op op;
		type::IncompleteType type;
		Expression expr;
	};


	struct Functional;
	struct Var;
	struct Assignable;
	class Statement;

	struct Integer final : public ExprBase {
		Integer(std::bitset<64> value, const SourceLocation & location)
			: Integer(static_cast<std::int64_t>(value.to_ullong()), location) {}

		Integer(std::int64_t value, const SourceLocation & location)
			: ExprBase(location), value(value) {}
		virtual ~Integer() = default;
		std::int64_t value;
	};



	struct Float final : public ExprBase {
		Float(stx::float64_t value, const SourceLocation & location)
			: ExprBase(location), value(value) {}
		virtual ~Float() = default;
		stx::float64_t value;
	};



	struct Bool final : public ExprBase {
		Bool(bool value, const SourceLocation & location)
			: ExprBase(location), value(value) {}
		virtual ~Bool() = default;
		bool value;
	};



	struct Null final : public ExprBase {
		Null(const SourceLocation & location)
			: ExprBase(location) {}
		virtual ~Null() = default;
	};



	struct Char final : public ExprBase {
		Char(std::uint8_t value, const SourceLocation & location)
			: ExprBase(location), value(value) {}
		virtual ~Char() = default;
		std::uint8_t value;
	};



	struct String final : public ExprBase {
		String(const std::string & value, const SourceLocation & location)
			: ExprBase(location), value(value) {}
		virtual ~String() = default;
		std::string value;
	};



	struct Array final: public ExprBase {
		Array(
			const SourceLocation & location,
			std::vector<Expression> elements)
			: ExprBase(location)
			, elements{std::move(elements)} {}

		std::vector<Expression> elements;
	};



	struct Tuple final: public ExprBase {
		Tuple(
			const SourceLocation & location,
			std::vector<Expression> elements)
			: ExprBase(location)
			, elements{std::move(elements)} {}
		virtual ~Tuple() = default;
		std::vector<Expression> elements;
	};



	struct Lambda final : public ExprBase {
		Lambda(
			std::unique_ptr<Function> fx,
			std::vector<std::unique_ptr<Var>> captures,
			const SourceLocation & location)
			: ExprBase(location)
			, fx(std::move(fx))
			, captures(std::move(captures)) {}
		virtual ~Lambda() = default;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};


	
	struct Index final : public ExprBase {
		Index(
			Expression expression,
			Expression index,
			const SourceLocation & location)
			: ExprBase(location)
			, expression(std::move(expression))
			, index(std::move(index)) {}
		virtual ~Index() = default;
		Expression expression;
		Expression index;
	};



	struct Var final : public ExprBase {
		Var(
			const std::string & name,
			const Namespace & namespaze,
			const SourceLocation & location)
			: ExprBase(location)
			, name{name}
			, namespaze{namespaze} {}

		virtual ~Var() = default;
		std::string name;
		Namespace namespaze;
	};



	struct GlobalVar final : public ExprBase {
		GlobalVar(
			const SourceLocation & location,
			const Namespace & namespaze,
			const std::string & name)
			: ExprBase(location)
			, name { name }
			, namespaze { namespaze } {}
		virtual ~GlobalVar() = default;
		std::string name;
		Namespace namespaze;
	};



	struct Member final : public ExprBase {
		Member(
			Expression expr,
			const std::string & name,
			const SourceLocation & location)
			: ExprBase(location)
			, expr(std::move(expr))
			, name(std::move(name)){};
		virtual ~Member() = default;
		Expression expr;
		std::string name;
	};



	struct Iife final : public ExprBase {
		Iife(
			const SourceLocation & location,
			std::unique_ptr<Statement> stmt,
			type::IncompleteType return_type) 
			: ExprBase(location)
			, stmt(std::move(stmt))
			, return_type{return_type} {}
		virtual ~Iife() = default;
		
		std::unique_ptr<Statement> stmt;
		type::IncompleteType return_type;
	};



	struct FxPointer final : public ExprBase {
		FxPointer(
			const std::string & name,
			const Namespace & namespaze,
			const std::size_t placeholders,
			const SourceLocation & location)
			: ExprBase(location)
			, name(name)
			, namespaze(namespaze)
			, placeholders(std::move(placeholders)) {}
		virtual ~FxPointer() = default;
		std::string name;
		Namespace namespaze;
		std::size_t placeholders;
		std::vector<type::IncompleteType> template_arguements;
	};



	struct Call final : public ExprBase {
		Call(
			Expression function_ptr,
			std::vector<Expression> parameters,
			const SourceLocation & location)
			: ExprBase(location)
			, function_ptr(std::move(function_ptr))
			, parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		Expression function_ptr;
		std::vector<Expression> parameters;
		std::vector<type::IncompleteType> template_args;
	};



	struct InitStruct final : public ExprBase {
		InitStruct(const SourceLocation & location)
			: ExprBase{location} {}
		virtual ~InitStruct() = default;
		struct Member {
			std::string name;
			Expression expr;
		};
		std::vector<Member> members;
	};



	struct ExprSwitch : public ExprBase {
		ExprSwitch(const SourceLocation & location) : ExprBase(location) {}
		Expression condition;
		std::vector<std::pair<
			Expression,
			Expression
		>> cases;
		Expression d3fault;
	};



	auto visit_expression(const ast::Expression & expr, auto && fx) {
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
}