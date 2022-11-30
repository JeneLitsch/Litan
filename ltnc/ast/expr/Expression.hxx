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
	


	struct DeclType : public Expression {
		DeclType(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Expression(location),
				expression(std::move(expression)) {}
		virtual ~DeclType() = default;
		std::unique_ptr<Expression> expression;
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
		enum class Type { NEG, NOT, NUL, BITNOT, DEREF };
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
			MLT, DIV, MOD, POW,
			BIGGER, SMALLER, BIGGEREQUAL, SMALLEREQUAL,
			EQUAL, UNEQUEL,
			SPACE_SHIP,
			SHIFT_L, SHIFT_R,
			AND, OR,
			NULLCO, ELVIS,
			BIT_OR, BIT_AND, BIT_XOR,
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



	struct Reflect : public Expression {
		struct NamespaceQuery {
			Namespace namespaze;
		};
		struct FunctionQuery {
			Namespace namespaze;
			std::string name;
			std::size_t arity;
		};
		using Query = std::variant<
			NamespaceQuery,
			FunctionQuery
		>;

		Reflect(
			const Query & query,
			const SourceLocation & location)
			:	Expression(location),
				query{query} {}
		virtual ~Reflect() = default;
		Query query;
	};



	struct TypedUnary final : public Expression {
	public:
		enum class Op {
			STATIC_CAST, DYNAMIC_CAST,
			STATIC_COPY, DYNAMIC_COPY
		};
		TypedUnary(
			Op op,
			const type::Type & type,
			std::unique_ptr<Expression> expr,
			const SourceLocation & location)
			:	Expression{location},
				op{op},
				type{type},
				expr{std::move(expr)} {}
		virtual ~TypedUnary() = default;
		Op op;
		type::Type type;
		std::unique_ptr<Expression> expr;
	};
}