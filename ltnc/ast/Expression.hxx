#pragma once
#include "Node.hxx"
#include <vector>
#include "Namespace.hxx"
namespace ltn::c::ast {
	struct Assignable;

	struct Expression : public Node {
		Expression(const SourceLocation & location) : Node(location) {}
		virtual ~Expression() = default;
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