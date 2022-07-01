#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	namespace {
		CompilerError undefined_enum(
			const ast::GlobalValue & node) {
			std::stringstream ss;
			ss << "Global value " << node.name << " is not defined";
			return CompilerError { ss.str(), node.location };
		}



		ExprCode compile_read_local_variable(const Variable & var) {
			InstructionBuffer buf;
			buf << ltn::inst::Readx { var.address };
			return ExprCode{ buf };
		}



		ExprCode compile_read_global_variable(const ast::Global & global, CompilerInfo & info) {
			Scope s{global.namespaze, false};
			return compile_expression(*global.expr, info, s);
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
			if(auto global = info.global_table.resolve(name, namespaze)) {
				return compile_read_global_variable(*global, info);
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



	ExprCode compile_global_value(
		const ast::GlobalValue & global_value,
		CompilerInfo & info,
		Scope & scope) {

		const auto enym = info.global_table.resolve(
			global_value.name,
			scope.get_namespace(),
			global_value.namespaze);
		
		if(!enym) {
			throw undefined_enum(global_value);
		}

		return compile_read_global_variable(*enym, info);
	}
}