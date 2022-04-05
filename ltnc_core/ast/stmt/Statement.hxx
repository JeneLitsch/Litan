#pragma once
#include "../Node.hxx"
#include <vector>
namespace ltn::c::ast {
	struct Expression;
	struct Assignable;
	struct Statement : public Node {
		Statement(const SourceLocation & location) : Node(location) {}
		virtual ~Statement() = default;
	};


	
	struct DoNothing : public Statement {
		DoNothing(const SourceLocation & location) : Statement(location) {}
		virtual ~DoNothing() = default;
	};



	struct Throw final : public Statement {
		Throw(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location) 
			:	Statement(location),
				expression(std::move(expression)) {}
		virtual ~Throw() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Block final : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements,
			const SourceLocation & location) 
			:	Statement(location),
				statements(std::move(statements)) {}
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;
	};



	struct NewVar final : public Statement {
		NewVar(
			const std::string & name,
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Statement(location),
				name(name),
				expression(std::move(expression)) {}
		virtual ~NewVar() = default;
		std::string name;
		std::unique_ptr<Expression> expression; 
	};



	struct NewConst final : public Statement {
		NewConst(
			const std::string & name,
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Statement(location),
				name(name),
				expression(std::move(expression)) {}
		virtual ~NewConst() = default;
		std::string name;
		std::unique_ptr<Expression> expression; 
	};



	struct IfElse final : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch,
			const SourceLocation & location)
			:	Statement(location),
				condition(std::move(condition)),
				if_branch(std::move(if_branch)),
				else_branch(std::move(else_branch)) {}
		virtual ~IfElse() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> if_branch;
		std::unique_ptr<Statement> else_branch;
	};



	struct While final : public Statement {
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


	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			:	Statement(location),
				body(std::move(body)) {}

		virtual ~InfiniteLoop() = default;
		std::unique_ptr<Statement> body;
	};



	struct For final : public Statement {
		For(
			std::unique_ptr<NewConst> var,
			std::unique_ptr<Expression> from,
			std::unique_ptr<Expression> to,
			std::unique_ptr<Expression> step,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			:	Statement(location),
				var(std::move(var)),
				from(std::move(from)),
				to(std::move(to)),
				step(std::move(step)),
				body(std::move(body)) {}

		virtual ~For() = default;
		std::unique_ptr<NewConst> var;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Expression> step;
		std::unique_ptr<Statement> body;
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Statement(location),
				expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Return final : public Statement {
		Return(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			:	Statement(location),
				expression(std::move(expression)) {}
		virtual ~Return() = default;
		std::unique_ptr<Expression> expression;
	};


	
	struct InitMember final : public Statement {
		InitMember(
			std::string member,
			std::string param,
			const SourceLocation & location)
			:	Statement(location),
				member(std::move(member)),
				param(std::move(param)) {}
		virtual ~InitMember() = default;
		std::string member;
		std::string param;
	};



	struct Assign final : public Statement {
	public:
		Assign(
			std::unique_ptr<Assignable> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Statement(location), l(std::move(l)), r(std::move(r)) {}
		virtual ~Assign() = default;
		std::unique_ptr<Assignable> l;
		std::unique_ptr<Expression> r;
	};



	struct Modify final : public Statement {
		enum class Type { ADD, SUB, MLT, DIV, MOD, SHIFT_L, SHIFT_R };
		Modify(
			Type type,
			std::unique_ptr<Assignable> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			:	Statement(location),
				type(type),
				l(std::move(l)),
				r(std::move(r)) {}
		virtual ~Modify() = default;
		Type type;
		std::unique_ptr<Assignable> l;
		std::unique_ptr<Expression> r;
	};
}