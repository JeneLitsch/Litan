#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	namespace {
		CompilerError undefined_enum(
			const ast::DefinitionValue & node) {
			std::stringstream ss;
			ss << "Definition value " << node.name << " is not defined";
			return CompilerError { ss.str(), node.location };
		}



		ExprCode compile_read_local_variable(const Variable & var) {
			InstructionBuffer buf;
			buf << ltn::inst::Readx { var.address };
			return ExprCode{ buf };
		}



		ExprCode compile_read_definition(const ast::Definition & definition, CompilerInfo & info) {
			Scope s{definition.namespaze, false};
			return compile_expression(*definition.expr, info, s);
		}



		bool is_inner_namespace(
			const ast::Namespace & call_ns,
			const ast::Namespace & fx_ns) {
			if(fx_ns.size() > call_ns.size()) return false;
			for(std::size_t i = 0; i < fx_ns.size(); i++) {
				if(call_ns[i] != fx_ns[i]) {
					return false;
				}
			}
			return true;
		}
	}



	void guard_private(
		const ast::Functional & fx,
		const ast::Namespace & call_ns,
		const SourceLocation & loc) {
		if(
			fx.pr1vate &&
			!is_inner_namespace(call_ns, fx.namespaze)) {
			throw CompilerError {
				"Function is not visible in current scope",
				loc
			};
		}
	}



	// compiles an variable read accessc
	ExprCode compile_read_variable(const ast::Var & expr, CompilerInfo & info, Scope & scope) {
		try {
			const auto var = scope.resolve(expr.name, expr.location);
			return compile_read_local_variable(var);
		}
		catch(const CompilerError & error) {
			const auto & name = expr.name;
			const auto & namespaze = scope.get_namespace();
			if(auto definition = info.definition_table.resolve(name, namespaze)) {
				return compile_read_definition(*definition, info);
			}
			throw error;
		}
	}

	
	ExprCode compile_read_member_access(
		const ast::Member & access,
		CompilerInfo & info,
		Scope & scope) {

		InstructionBuffer buf;
		buf << compile_expression(*access.expr, info, scope).code;
		const auto id = info.member_table.get_id(access.name);
		buf << ltn::inst::MemberRead{id};
		return ExprCode{ buf };
	}



	ExprCode compile_definition_value(
		const ast::DefinitionValue & definition_value,
		CompilerInfo & info,
		Scope & scope) {

		const auto enym = info.definition_table.resolve(
			definition_value.name,
			scope.get_namespace(),
			definition_value.namespaze);
		
		if(!enym) {
			throw undefined_enum(definition_value);
		}

		return compile_read_definition(*enym, info);
	}
}