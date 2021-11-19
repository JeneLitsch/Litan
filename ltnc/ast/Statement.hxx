#pragma once
#include "Node.hxx"
#include "Expression.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Statement : public Node {
		Statement(const lex::DebugInfo & debugInfo) : Node(debugInfo) {}
		virtual ~Statement() = default;
	};

	struct Block : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements,
			const lex::DebugInfo & debugInfo) 
			:	Statement(debugInfo),
				statements(std::move(statements)) {}
		virtual ~Block() = default;
		const std::vector<std::unique_ptr<Statement>> statements;
	};

	struct IfElse : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> ifBranch,
			std::unique_ptr<Statement> elseBranch,
			const lex::DebugInfo & debugInfo)
			:	Statement(debugInfo),
				condition(std::move(condition)),
				ifBranch(std::move(ifBranch)),
				elseBranch(std::move(elseBranch)) {}
		virtual ~IfElse() = default;
		const std::unique_ptr<Expression> condition;
		const std::unique_ptr<Statement> ifBranch;
		const std::unique_ptr<Statement> elseBranch;
	};

	struct While : public Statement {
		While(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body,
			const lex::DebugInfo & debugInfo)
			:	Statement(debugInfo),
				condition(std::move(condition)),
				body(std::move(body)) {}

		virtual ~While() = default;
		const std::unique_ptr<Expression> condition;
		const std::unique_ptr<Statement> body;
	};

	struct StatementExpression : public Statement {
		StatementExpression(
			std::unique_ptr<Expression> expression,
			const lex::DebugInfo & debugInfo)
			:	Statement(debugInfo),
				expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		const std::unique_ptr<Expression> expression;
	};

	struct Return : public Statement {
		Return(
			std::unique_ptr<Expression> expression,
			const lex::DebugInfo & debugInfo)
			:	Statement(debugInfo),
				expression(std::move(expression)) {}
		virtual ~Return() = default;
		const std::unique_ptr<Expression> expression;
	};

	struct NewVar : public Statement {
		enum class MemoryClass { VAR, REF };
		NewVar(
			MemoryClass memoryClass, 
			type::Type type,
			const std::string & name,
			std::unique_ptr<Assign> assign,
			const lex::DebugInfo & debugInfo)
			:	Statement(debugInfo),
				memoryClass(memoryClass),
				type(std::move(type)),
				name(name),
				assign(std::move(assign)) {}
		virtual ~NewVar() = default;
		const MemoryClass memoryClass;
		const type::Type type; 
		const std::string name;
		const std::unique_ptr<Assign> assign; 
	};
}