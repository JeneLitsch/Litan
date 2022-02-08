#pragma once
#include "Node.hxx"
#include "Expression.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Statement : public Node {
		Statement(const SourceLocation & location) : Node(location) {}
		virtual ~Statement() = default;
	};

	struct Block : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements,
			const SourceLocation & location) 
			:	Statement(location),
				statements(std::move(statements)) {}
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;
	};

	struct NewVar : public Statement {
		NewVar(
			const std::string & name,
			std::unique_ptr<Expression> right,
			const SourceLocation & location)
			:	Statement(location),
				name(name),
				right(std::move(right)) {}
		virtual ~NewVar() = default;
		std::string name;
		std::unique_ptr<Expression> right; 
	};

	struct NewConst : public Statement {
		NewConst(
			const std::string & name,
			std::unique_ptr<Expression> right,
			const SourceLocation & location)
			:	Statement(location),
				name(name),
				right(std::move(right)) {}
		virtual ~NewConst() = default;
		std::string name;
		std::unique_ptr<Expression> right; 
	};

	struct IfElse : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> ifBranch,
			std::unique_ptr<Statement> elseBranch,
			const SourceLocation & location)
			:	Statement(location),
				condition(std::move(condition)),
				ifBranch(std::move(ifBranch)),
				elseBranch(std::move(elseBranch)) {}
		virtual ~IfElse() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> ifBranch;
		std::unique_ptr<Statement> elseBranch;
	};


	struct While : public Statement {
		While(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			:	Statement(location),
				condition(std::move(condition)),
				body(std::move(body)) {}

		virtual ~While() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};

	struct For : public Statement {
		For(
			std::unique_ptr<NewVar> var,
			std::unique_ptr<Expression> from,
			std::unique_ptr<Expression> to,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			:	Statement(location),
				var(std::move(var)),
				from(std::move(from)),
				to(std::move(to)),
				body(std::move(body)) {}

		virtual ~For() = default;
		std::unique_ptr<NewVar> var;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Statement> body;
	};

	struct StatementExpression : public Statement {
		StatementExpression(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Statement(location),
				expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;
	};

	struct Return : public Statement {
		Return(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Statement(location),
				expression(std::move(expression)) {}
		virtual ~Return() = default;
		std::unique_ptr<Expression> expression;
	};
}