#pragma once
#include <vector>
#include "../Node.hxx"
#include "../Namespace.hxx"
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
}