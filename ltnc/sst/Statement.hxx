#pragma once
#include <vector>
#include "Node.hxx"
#include "Switch.hxx"
#include "ltnc/type/Type.hxx"
#include "ltn/casts.hxx"
#include "Binding.hxx"

namespace ltn::c::sst {
	struct Expression;
	struct Assignable;
	class Statement : public Node {
	public:
		Statement(
			std::size_t nested_alloc_count,
			std::size_t direct_alloc_count)
			: local_vars_count{nested_alloc_count}
			, direct_allocation_count{direct_alloc_count} {}
		virtual ~Statement() = default;

		std::size_t nested_alloc() const { return local_vars_count; }
		std::size_t direct_alloc() const { return direct_allocation_count; }
	private:
		std::size_t local_vars_count;
		std::size_t direct_allocation_count;
	};
	using stmt_ptr = std::unique_ptr<Statement>;


	
	struct DoNothing : public Statement {
		DoNothing(std::size_t local_vars, std::size_t direct_allocation)
		: Statement{local_vars, direct_allocation} {}
		virtual ~DoNothing() = default;
	};



	struct Throw final : public Statement {
		Throw(
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Expression> expression) 
			: Statement{local_vars, direct_allocation}
			, expression(std::move(expression)) {}
		virtual ~Throw() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Block final : public Statement {
		Block(
			std::size_t local_vars, std::size_t direct_allocation,
			std::vector<std::unique_ptr<Statement>> statements) 
			: Statement{local_vars, direct_allocation}
			, statements(std::move(statements)) {}
		virtual ~Block() = default;
		std::vector<std::unique_ptr<Statement>> statements;
	};



	struct NewVar final : public Statement {
		NewVar(
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Binding> binding,
			std::unique_ptr<Expression> expression)
			: Statement{local_vars, direct_allocation}
			, binding{std::move(binding)}
			, expression(std::move(expression)) {}
		virtual ~NewVar() = default;
		std::unique_ptr<Binding> binding;
		std::unique_ptr<Expression> expression;
	};



	struct IfElse final : public Statement {
		IfElse(
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> if_branch,
			std::unique_ptr<Statement> else_branch)
			: Statement{local_vars, direct_allocation}
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
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Expression> condition,
			std::unique_ptr<Statement> body)
			: Statement{local_vars, direct_allocation}
			, condition(std::move(condition))
			, body(std::move(body)) {}

		virtual ~While() = default;
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Statement> body;
	};


	struct InfiniteLoop final : public Statement {
		InfiniteLoop(
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Statement> body)
			: Statement{local_vars, direct_allocation}
			, body(std::move(body)) {}

		virtual ~InfiniteLoop() = default;
		std::unique_ptr<Statement> body;
	};



	struct For final : public Statement {
		For(
			std::size_t local_vars, std::size_t direct_allocation,
			std::string label,
			std::size_t index_addr,
			std::unique_ptr<Expression> from,
			std::unique_ptr<Expression> to,
			std::unique_ptr<Expression> step,
			std::unique_ptr<Statement> body)
			: Statement{local_vars, direct_allocation}
			, label{label}
			, index_addr{index_addr}
			, from(std::move(from))
			, to(std::move(to))
			, step(std::move(step))
			, body(std::move(body)) {}

		virtual ~For() = default;
		std::string label;
		std::size_t index_addr;
		std::unique_ptr<Expression> from;
		std::unique_ptr<Expression> to;
		std::unique_ptr<Expression> step;
		std::unique_ptr<Statement> body;
	};



	struct StatementExpression final : public Statement {
		StatementExpression(
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Expression> expression)
			: Statement{local_vars, direct_allocation}
			, expression(std::move(expression)) {}
		virtual ~StatementExpression() = default;
		std::unique_ptr<Expression> expression;
	};



	struct Return final : public Statement {
		Return(
			std::size_t local_vars, std::size_t direct_allocation,
			std::unique_ptr<Expression> expression,
			std::optional<std::string> overide_label)
			: Statement{local_vars, direct_allocation}
			, expression(std::move(expression))
			, overide_label{overide_label} {}
		virtual ~Return() = default;
		std::unique_ptr<Expression> expression;
		std::optional<std::string> overide_label;
	};


	
	struct InitMember final : public Statement {
		InitMember(
			std::size_t local_vars, std::size_t direct_allocation,
			std::size_t object_addr,
			std::size_t member_addr,
			std::size_t param_addr,
			type::Type type)
			: Statement{local_vars, direct_allocation}
			, object_addr(object_addr)
			, member_addr(member_addr)
			, param_addr(param_addr)
			, type{type} {}
		virtual ~InitMember() = default;
		std::size_t object_addr;
		std::size_t member_addr;
		std::size_t param_addr;
		type::Type type;
	};



	struct AssignGlobal final : public Statement {
		AssignGlobal(
			std::size_t local_vars,
			std::size_t direct_allocation,
			std::uint64_t addr,
			std::unique_ptr<Expression> r)
			: Statement{local_vars, direct_allocation}
			, addr{addr}
			, r(std::move(r)) {}
		virtual ~AssignGlobal() = default;
		std::uint64_t addr;
		std::unique_ptr<Expression> r;
	};



	struct AssignMember final : public Statement {
		AssignMember(
			std::size_t local_vars,
			std::size_t direct_allocation,
			std::unique_ptr<Expression> object,
			std::uint64_t addr,
			std::unique_ptr<Expression> r)
			: Statement{local_vars, direct_allocation}
			, object{std::move(object)}
			, addr{addr}
			, r(std::move(r)) {}
		virtual ~AssignMember() = default;
		std::unique_ptr<Expression> object;
		std::uint64_t addr;
		std::unique_ptr<Expression> r;
	};



	struct AssignLocal final : public Statement {
		AssignLocal(
			std::size_t local_vars,
			std::size_t direct_allocation,
			std::uint64_t addr,
			std::unique_ptr<Expression> r)
			: Statement{local_vars, direct_allocation}
			, addr{addr}
			, r(std::move(r)) {}
		virtual ~AssignLocal() = default;
		std::uint64_t addr;
		std::unique_ptr<Expression> r;
	};


	struct AssignIndex final : public Statement {
		AssignIndex(
			std::size_t local_vars,
			std::size_t direct_allocation,
			std::unique_ptr<Expression> range,
			std::unique_ptr<Expression> index,
			std::unique_ptr<Expression> r)
			: Statement{local_vars, direct_allocation}
			, range{std::move(range)}
			, index{std::move(index)}
			, r(std::move(r)) {}
		virtual ~AssignIndex() = default;
		std::unique_ptr<Expression> range;
		std::unique_ptr<Expression> index;
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
		if(auto s = as<sst::AssignLocal>(stmt)) return fx(*s);
		if(auto s = as<sst::AssignIndex>(stmt)) return fx(*s);
		if(auto s = as<sst::AssignMember>(stmt)) return fx(*s);
		if(auto s = as<sst::AssignGlobal>(stmt)) return fx(*s);
		throw std::runtime_error{"Unknown SST statement"};
	}
}