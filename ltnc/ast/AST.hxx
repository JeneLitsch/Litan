#pragma once
#include "ltnc/ast/bind/Binding.hxx"
#include "ltnc/ast/decl/Declaration.hxx"
#include "ltnc/ast/decl/Function.hxx"
#include "ltnc/ast/expr/Expression.hxx"
#include "ltnc/ast/stmt/Statement.hxx"

namespace ltn::c::ast {
	using expr_ptr = std::unique_ptr<Expression>;
	using defn_ptr = std::unique_ptr<Definition>;
	using glob_ptr = std::unique_ptr<Global>;
	using stmt_ptr = std::unique_ptr<Statement>;
	using func_ptr = std::unique_ptr<Functional>;
	using enum_ptr = std::unique_ptr<Enumeration>;
	using bind_ptr = std::unique_ptr<Binding>;
	using type_ptr = std::unique_ptr<Type>;
	
	struct Program {
		std::vector<func_ptr> functions;
		std::vector<defn_ptr> definitions;
		std::vector<glob_ptr> globals;
		std::vector<enum_ptr> enums;
	};
}