#pragma once
#include "Node.hxx"
#include "Expression.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Statement : public Node {
		virtual ~Statement() = default;
	};

	struct Block : public Statement {
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;
	};

	struct IfElse : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> ifBranch,
			std::unique_ptr<Statement> elseBranch)
			:	condition(std::move(condition)),
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
			std::unique_ptr<Statement> body)
			:	condition(std::move(condition)),
				body(std::move(body)) {}

		virtual ~While() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};

	struct StatementExpression : public Statement {
		StatementExpression(std::unique_ptr<Expression> expression)
			:	expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;
	};

	struct NewVar : public Statement {
		enum class MemoryClass { VAR, REF };
		NewVar(
			MemoryClass memoryClass, 
			std::unique_ptr<Type> type,
			const std::string & name,
			std::unique_ptr<Assign> assign)
			:	memoryClass(memoryClass),
				type(std::move(type)),
				name(name),
				assign(std::move(assign)) {}
		virtual ~NewVar() = default;
		MemoryClass memoryClass;
		std::unique_ptr<Type> type; 
		std::string name;
		std::unique_ptr<Assign> assign; 
	};
}