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
			std::unique_ptr<Statement> stmt) 
			:	Primary(location), 
				stmt(std::move(stmt)) {}
		virtual ~Iife() = default;
		
		std::unique_ptr<Statement> stmt;
	};



	struct Call final : public Primary {
	public:
		Call(
			const std::string & name,
			const Namespace & namespaze,
			std::vector<std::unique_ptr<Expression>> parameters,
			const SourceLocation & location)
			:	Primary(location),
				name(name),
				namespaze(namespaze),
				parameters(std::move(parameters)) {}
		virtual ~Call() = default;
		std::string name;
		Namespace namespaze;
		std::vector<std::unique_ptr<Expression>> parameters;
	};



	struct GlobalValue final : public Primary {
	public:
		GlobalValue(
			const std::string & name,
			const Namespace & namespaze,
			const SourceLocation & location)
			:	Primary(location),
				name(name),
				namespaze(namespaze) {}
		virtual ~GlobalValue() = default;
		std::string name;
		Namespace namespaze;
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
}