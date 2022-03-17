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



	struct Nullco : public Expression {
		Nullco(
			const SourceLocation & location,
			std::unique_ptr<Expression> if_expr,
			std::unique_ptr<Expression> else_expr) 
			:	Expression(location),
				if_expr(std::move(if_expr)),
				else_expr(std::move(else_expr)) {}
		virtual ~Nullco() = default;
	
		std::unique_ptr<Expression> if_expr;
		std::unique_ptr<Expression> else_expr;
	};



	struct Elvis : public Expression {
		Elvis(
			const SourceLocation & location,
			std::unique_ptr<Expression> if_expr,
			std::unique_ptr<Expression> else_expr) 
			:	Expression(location), 
				if_expr(std::move(if_expr)),
				else_expr(std::move(else_expr)) {}
		virtual ~Elvis() = default;
	
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
		Binary(
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Expression(location),
				l(std::move(l)),
				r(std::move(r)) {}
		virtual ~Binary() = default;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};



	struct SimpleBinary : public Binary {
		enum class Type {
			ADD, SUB,
			MLT, DIV, MOD,
			BIGGER, SMALLER, BIGGEREQUAL, SMALLEREQUAL,
			EQUAL, UNEQUEL,
			SPACE_SHIP, APPROX, NOTPROX,
			SHIFT_L, SHIFT_R, };
		SimpleBinary(
			Type type,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Binary(std::move(l), std::move(r), location),
				type(type) {}
		virtual ~SimpleBinary() = default;
		Type type;
	};



	struct Logical : public Binary {
		enum class Type {
			AND, OR,
		};
		Logical(
			Type type,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Binary(std::move(l), std::move(r), location),
				type(type) {}
		virtual ~Logical() = default;
		Type type;
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



	struct EnumValue : public Primary {
	public:
		EnumValue(
			const std::string & enum_name,
			const std::string & value_name,
			const Namespace & namespaze,
			const SourceLocation & location)
			:	Primary(location),
				enum_name(enum_name),
				value_name(value_name),
				namespaze(namespaze) {}
		virtual ~EnumValue() = default;
		std::string enum_name;
		std::string value_name;
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