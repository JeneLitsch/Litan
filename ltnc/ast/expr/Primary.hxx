#pragma once
#include "Expression.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Assignable;
	struct Statement;

	struct Primary : public Expression {
		Primary(const SourceLocation & location) : Expression(location) {}
		virtual ~Primary() = default;
	};



	struct Iife final : public Primary {
		Iife(
			const SourceLocation & location,
			std::unique_ptr<Statement> stmt,
			type::Type return_type) 
			:	Primary(location), 
				stmt(std::move(stmt)),
				return_type{return_type} {}
		virtual ~Iife() = default;
		
		std::unique_ptr<Statement> stmt;
		type::Type return_type;
	};



	struct StaticCast final : public Primary {
	public:
		StaticCast(
			const type::Type & type,
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			:	Primary(location),
				type{type},
				expr{std::move(expr)} {}
		virtual ~StaticCast() = default;
		type::Type type;
		std::unique_ptr<Expression> expr;
	};



	struct DynamicCast final : public Primary {
	public:
		DynamicCast(
			const type::Type & type,
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			:	Primary(location),
				type{type},
				expr{std::move(expr)} {}
		virtual ~DynamicCast() = default;
		type::Type type;
		std::unique_ptr<Expression> expr;
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
	};


	using ExprSwitch = Switch<Primary, Expression>;
}