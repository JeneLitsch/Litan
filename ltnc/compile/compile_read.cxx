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



		ExprResult compile_read_local_variable(const Variable & var) {
			InstructionBuffer buf;
			buf << inst::read_x(var.address);
			return ExprResult{ 
				.code = buf,
				.deduced_type = var.type
			};
		}



		ExprResult compile_read_definition(const ast::Definition & definition, CompilerInfo & info) {
			MajorScope s{definition.namespaze, false};
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
	ExprResult compile_read_variable(const ast::Var & expr, CompilerInfo & info, Scope & scope) {
		try {
			if(!expr.namespaze.empty()) throw CompilerError{
				"Local variable must not have a namespace"
			};
			const auto var = scope.resolve(expr.name, expr.location);
			return compile_read_local_variable(var);
		}
		catch(const CompilerError & error) {
			const auto & name = expr.name;
			const auto & namespaze = scope.get_namespace();
			if(const auto * definition = info.definition_table.resolve(name, namespaze, expr.namespaze)) {
				InstructionBuffer buf;
				buf << inst::global_read(definition->id);
				return ExprResult{ buf };
			}
			throw error;
		}
	}

	
	ExprResult compile_read_member_access(
		const ast::Member & access,
		CompilerInfo & info,
		Scope & scope) {

		InstructionBuffer buf;
		buf << compile_expression(*access.expr, info, scope).code;
		const auto id = info.member_table.get_id(access.name);
		buf << inst::member_read(id);
		return ExprResult{ buf };
	}
}