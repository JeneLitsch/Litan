#pragma once
#include "Node.hxx"
#include <vector>
#include "Namespace.hxx"
namespace ltn::c::ast {
	struct Assignable;
	struct Statement;



	struct Expression : public Node {
		Expression(const SourceLocation & location) : Node(location) {}
		virtual ~Expression() = default;
	};
	


	struct Ternary : public Expression {
		Ternary(
			const SourceLocation & location,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> if_expr,
			std::unique_ptr<Expression> else_expr) 
			:	Expression(location),
				condition(std::move(condition)),
				if_expr(std::move(if_expr)),
				else_expr(std::move(else_expr)) {}
		virtual ~Ternary() = default;
	
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> if_expr;
		std::unique_ptr<Expression> else_expr;
	};



	struct Primary : public Expression {
		Primary(const SourceLocation & location) : Expression(location) {}
		virtual ~Primary() = default;
	};



	struct Unary : public Expression {
		enum class Type { NEG, NOT, NUL };
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
			MLT, DIV, MOD,
			BIGGER, SMALLER, BIGGEREQUAL, SMALLEREQUAL,
			EQUAL, UNEQUEL,
			SPACE_SHIP, APPROX, NOTPROX,
			SHIFT_L, SHIFT_R,
			AND, OR,
			NULLCO, ELVIS,
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



	struct Iife : public Primary {
		Iife(
			const SourceLocation & location,
			std::unique_ptr<Statement> stmt) 
			:	Primary(location), 
				stmt(std::move(stmt)) {}
		virtual ~Iife() = default;
		
		std::unique_ptr<Statement> stmt;
	};



	struct Call : public Primary {
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



	struct GlobalValue : public Primary {
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



	struct FxPointer : public Primary {
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