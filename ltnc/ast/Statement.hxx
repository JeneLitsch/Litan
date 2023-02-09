#pragma once
#include <vector>
#include "Node.hxx"
#include "Switch.hxx"
#include "ltnc/type/Type.hxx"
#include "ltn/casts.hxx"
#include "Binding.hxx"

namespace ltn::c::ast {
	struct Expression;
	struct Assignable;
	class Statement : public Node {
	public:
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
			: Statement(location)
			, expression(std::move(expression)) {}
		virtual ~Throw() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Block final : public Statement {
		Block(
			std::vector<std::unique_ptr<Statement>> statements,
			const SourceLocation & location) 
			: Statement(location)
			, statements(std::move(statements)) {}
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;
	};



	struct NewVar final : public Statement {
		NewVar(
			std::unique_ptr<Binding> binding,
			std::unique_ptr<Expression> expression,
			const SourceLocation & location,
			const std::optional<type::IncompleteType> & type = type::IncompleteType{type::Any{}})
			: Statement(location)
			, binding(std::move(binding))
			, expression(std::move(expression))
			, type{type} {}
		virtual ~NewVar() = default;
		std::unique_ptr<Binding> binding;		
		std::unique_ptr<Expression> expression;
		std::optional<type::IncompleteType> type;
	};



	struct IfElse final : public Statement {
		IfElse(
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch,
			const SourceLocation & location)
			: Statement(location)
			, condition(std::move(condition))
			, if_branch(std::move(if_branch))
			, else_branch(std::move(else_branch)) {}
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
			: Statement(location)
			, condition(std::move(condition))
			, body(std::move(body)) {}

		virtual ~While() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};



	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, body(std::move(body)) {}

		virtual ~InfiniteLoop() = default;
		std::unique_ptr<Statement> body;
	};



	struct For final : public Statement {
		For(
			std::string index_name,
			std::unique_ptr<Expression> from,
			std::unique_ptr<Expression> to,
			std::unique_ptr<Expression> step,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Statement(location)
			, index_name(std::move(index_name))
			, from(std::move(from))
			, to(std::move(to))
			, step(std::move(step))
			, body(std::move(body)) {}

		virtual ~For() = default;
		std::string index_name;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Expression> step;
		std::unique_ptr<Statement> body;
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			: Statement(location)
			, expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Return final : public Statement {
		Return(
			std::unique_ptr<Expression> expression,
			const SourceLocation & location)
			: Statement(location)
			, expression(std::move(expression)) {}
		virtual ~Return() = default;
		std::unique_ptr<Expression> expression;
	};


	
	struct InitMember final : public Statement {
		InitMember(
			std::string member,
			std::string param,
			type::IncompleteType type,
			const SourceLocation & location)
			: Statement(location)
			, member(std::move(member))
			, param(std::move(param))
			, type{type} {}
		virtual ~InitMember() = default;
		std::string member;
		std::string param;
		type::IncompleteType type;
	};



	struct Assign final : public Statement {
	public:
		Assign(
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r,
			const SourceLocation & location)
			: Statement(location)
			, l(std::move(l))
			, r(std::move(r)) {}
		virtual ~Assign() = default;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};

	using StmtSwitch = Switch<Statement>;



	auto visit_statement(const ast::Statement & stmt, auto && fx) {
		if(auto s = as<ast::Block>(stmt)) return fx(*s);
		if(auto s = as<ast::IfElse>(stmt)) return fx(*s);
		if(auto s = as<ast::While>(stmt)) return fx(*s);
		if(auto s = as<ast::InfiniteLoop>(stmt)) return fx(*s);
		if(auto s = as<ast::For>(stmt)) return fx(*s);
		if(auto s = as<ast::NewVar>(stmt)) return fx(*s);
		if(auto s = as<ast::Return>(stmt)) return fx(*s);
		if(auto s = as<ast::Throw>(stmt)) return fx(*s);
		if(auto s = as<ast::StmtSwitch>(stmt)) return fx(*s);
		if(auto s = as<ast::StatementExpression>(stmt)) return fx(*s);
		if(auto s = as<ast::DoNothing>(stmt)) return fx(*s);
		if(auto s = as<ast::Assign>(stmt)) return fx(*s);
		throw std::runtime_error{"Unknown AST statement"};
	}
}