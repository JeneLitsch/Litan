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

	struct ExpressionCore;
	struct Expression {
		template<typename T>
		Expression(T && expr) 
			: core{ std::make_unique<ExpressionCore>(std::move(expr))} {}

		Expression(const std::nullptr_t &) 
			: core{ nullptr } {}

		Expression(Expression &&) = default;
		Expression & operator=(Expression &&) = default;

		operator bool() const {
			return static_cast<bool>(core);
		}
		
		std::unique_ptr<ExpressionCore> core;
	};



	struct ForwardDynamicCall {
		ForwardDynamicCall(
			std::uint64_t addr,
			std::uint64_t arity,
			const SourceLocation & location)
			: addr{addr}
			, arity{arity} {}
		virtual ~ForwardDynamicCall() = default;
		SourceLocation location;
		std::uint64_t addr;
		std::uint64_t arity;
	};
	


	struct Ternary {
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
			: op(op)
			, expression(std::move(expression)) {}
		virtual ~Unary() = default;
		SourceLocation location;
		Op op;
		Expression expression;
	};



	struct Binary {
		using Op = BinaryOp;
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
		SourceLocation location;
		Query query;
	};



	struct TypedUnary final {
		using Op = TypedUnaryOp;
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
			: value(value) {}
		virtual ~Integer() = default;
		SourceLocation location;
		std::int64_t value;
	};



	struct Float final {
		Float(stx::float64_t value, const SourceLocation & location)
			: value(value) {}
		virtual ~Float() = default;
		SourceLocation location;
		stx::float64_t value;
	};



	struct Bool final {
		Bool(bool value, const SourceLocation & location)
			: value(value) {}
		virtual ~Bool() = default;
		SourceLocation location;
		bool value;
	};



	struct Null final {
		Null(const SourceLocation & location) {}
		virtual ~Null() = default;
		SourceLocation location;
	};



	struct Char final {
		Char(std::uint8_t value, const SourceLocation & location)
			: value(value) {}
		virtual ~Char() = default;
		SourceLocation location;
		std::uint8_t value;
	};



	struct String final {
		String(const std::string & value, const SourceLocation & location)
			: value(value) {}
		virtual ~String() = default;
		SourceLocation location;
		std::string value;
	};



	struct Array final{
		SourceLocation location;
		std::vector<Expression> elements;
	};



	struct Tuple final{
		SourceLocation location;
		std::vector<Expression> elements;
	};



	struct Lambda final {
		SourceLocation location;
		std::unique_ptr<Function> fx;
		std::vector<std::unique_ptr<Var>> captures;
	};


	
	struct Index final {
		Index(
			Expression expression,
			Expression index,
			const SourceLocation & location)
			: expression(std::move(expression))
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
			: name{name}
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
			: name { name }
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
			: expr(std::move(expr))
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
			: stmt(std::move(stmt))
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
			: name(name)
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
			: function_ptr(std::move(function_ptr))
			, parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		SourceLocation location;
		Expression function_ptr;
		std::vector<Expression> parameters;
		std::vector<type::IncompleteType> template_args;
	};



	struct InitStruct final {
		struct Member {
			std::string name;
			Expression expr;
		};
		SourceLocation location;
		std::vector<Member> members;
	};



	struct ExprSwitch : Switch<Expression> {
		SourceLocation location;
	};





	struct ExpressionCore {
		using Variant = std::variant<
			Binary,
			Unary,
			Integer,
			Float,
			Bool,
			Char,
			Null,
			String,
			Array,
			Tuple,
			Call,
			Var,
			Index,
			Lambda,
			FxPointer,
			Member,
			GlobalVar,
			Iife,
			Ternary,
			ExprSwitch,
			TypedUnary,
			Reflect,
			ForwardDynamicCall,
			InitStruct
		>;
		Variant variant;
		ExpressionCore(auto && expr) : variant(std::move(expr)) {}
	};



	auto visit_expression(const ast::Expression & expr, auto && fx) {
		return std::visit(fx, expr.core->variant);
	}



	auto location(const ast::Expression & expr) {
		return visit_expression(expr, [] (const auto & e) {
			return e.location;
		});
	}
}