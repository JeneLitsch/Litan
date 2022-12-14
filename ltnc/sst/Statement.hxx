#pragma once
#include <vector>
#include "Node.hxx"
#include "Switch.hxx"
#include "ltnc/type/Type.hxx"
#include "ltn/casts.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Assignable;
	struct Statement : public Node {
		Statement(std::size_t local_vars, bool direct_allocation)
		: local_vars{local_vars}, direct_allocation{direct_allocation} {}
		virtual ~Statement() = default;
		std::size_t local_vars;
		bool direct_allocation;
	};


	
	struct DoNothing : public Statement {
		DoNothing(std::size_t local_vars, bool direct_allocation)
		: Statement{local_vars, direct_allocation} {}
		virtual ~DoNothing() = default;
	};



	struct Throw final : public Statement {
		Throw(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Expression> expression) 
			: 
				Statement{local_vars, direct_allocation},
				expression(std::move(expression)) {}
		virtual ~Throw() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Block final : public Statement {
		Block(
			std::size_t local_vars, bool direct_allocation,
			std::vector<std::unique_ptr<Statement>> statements) 
			:	
				Statement{local_vars, direct_allocation},
				statements(std::move(statements)) {}
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;
	};



	struct NewVar final : public Statement {
		NewVar(
			std::size_t local_vars, bool direct_allocation,
			const std::string & name,
			std::unique_ptr<Expression> expression,
			const std::variant<type::IncompleteType, type::Auto> & type = type::IncompleteType{type::Any{}})
			:	
				Statement{local_vars, direct_allocation},
				name(name),
				expression(std::move(expression)),
				type{type} {}
		virtual ~NewVar() = default;
		std::string name;
		std::unique_ptr<Expression> expression;
		std::variant<type::IncompleteType, type::Auto> type;
	};


	struct IfElse final : public Statement {
		IfElse(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch)
			:	
				Statement{local_vars, direct_allocation},
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
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body,
			const type::Type & type)
			:	
				Statement{local_vars, direct_allocation},
				condition(std::move(condition)),
				body(std::move(body)) {}

		virtual ~While() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};


	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Statement> body)
			:	
				Statement{local_vars, direct_allocation},
				body(std::move(body)) {}

		virtual ~InfiniteLoop() = default;
		std::unique_ptr<Statement> body;
	};



	struct For final : public Statement {
		For(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<NewVar> var,
			std::unique_ptr<Expression> from,
			std::unique_ptr<Expression> to,
			std::unique_ptr<Expression> step,
			std::unique_ptr<Statement> body)
			:	
				Statement{local_vars, direct_allocation},
				var(std::move(var)),
				from(std::move(from)),
				to(std::move(to)),
				step(std::move(step)),
				body(std::move(body)) {}

		virtual ~For() = default;
		std::unique_ptr<NewVar> var;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Expression> step;
		std::unique_ptr<Statement> body;
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Expression> expression)
			:	
				Statement{local_vars, direct_allocation},
				expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Return final : public Statement {
		Return(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Expression> expression)
			:	
				Statement{local_vars, direct_allocation},
				expression(std::move(expression)) {}
		virtual ~Return() = default;
		std::unique_ptr<Expression> expression;
	};


	
	struct InitMember final : public Statement {
		InitMember(
			std::size_t local_vars, bool direct_allocation,
			std::string member,
			std::string param,
			type::IncompleteType type)
			:	
				Statement{local_vars, direct_allocation},
				member(std::move(member)),
				param(std::move(param)),
				type{type} {}
		virtual ~InitMember() = default;
		std::string member;
		std::string param;
		type::IncompleteType type;
	};



	struct Assign final : public Statement {
	public:
		Assign(
			std::size_t local_vars, bool direct_allocation,
			std::unique_ptr<Expression> l,
			std::unique_ptr<Expression> r)
			: Statement{local_vars, direct_allocation}, l(std::move(l)), r(std::move(r)) {}
		virtual ~Assign() = default;
		std::unique_ptr<Expression> l;
		std::unique_ptr<Expression> r;
	};

	using StmtSwitch = Switch<Statement, Statement>;



	auto visit_statement(const sst::Statement & stmt, auto && fx) {
		if(auto s = as<sst::Block>(stmt)) return fx(*s);
		if(auto s = as<sst::IfElse>(stmt)) return fx(*s);
		if(auto s = as<sst::While>(stmt)) return fx(*s);
		if(auto s = as<sst::InfiniteLoop>(stmt)) return fx(*s);
		if(auto s = as<sst::For>(stmt)) return fx(*s);
		if(auto s = as<sst::NewVar>(stmt)) return fx(*s);
		if(auto s = as<sst::Return>(stmt)) return fx(*s);
		if(auto s = as<sst::Throw>(stmt)) return fx(*s);
		if(auto s = as<sst::InitMember>(stmt)) return fx(*s);
		if(auto s = as<sst::StmtSwitch>(stmt)) return fx(*s);
		if(auto s = as<sst::StatementExpression>(stmt)) return fx(*s);
		if(auto s = as<sst::DoNothing>(stmt)) return fx(*s);
		if(auto s = as<sst::Assign>(stmt)) return fx(*s);
		throw std::runtime_error{"Unknown statement"};
	}
}