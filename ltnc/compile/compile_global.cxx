#include "compile.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		auto undefined(const ast::GlobalVar & global) {
			std::ostringstream oss;
			oss
				<< "Undefined global variable "
				<< global.namespaze.to_string() << global.name;

			return CompilerError { oss.str(), global.location };
		}

		auto undefined(const ast::DefinitionValue & def) {
			std::ostringstream oss;
			oss
				<< "Undefined definition "
				<< def.namespaze.to_string() << def.name;

			return CompilerError { oss.str(), def.location };
		}

		auto & resolve_static(const auto & statik, auto & table, Scope & scope) {
			const auto static_var = table.resolve(
				statik.name,
				scope.get_namespace(),
				statik.namespaze);

			if(!static_var) throw undefined(statik);
			return *static_var;
		}
	}

	ExprResult compile_read_static(const ast::GlobalVar & global_var, CompilerInfo & info, Scope & scope) {
		auto & global = resolve_static(global_var, info.global_table, scope);
		InstructionBuffer buf;
		buf << inst::global_read(global.id);
		return ExprResult{ 
			.code = buf,
			.deduced_type = global.type
		};
	}



	ExprResult compile_write_static(const ast::GlobalVar & global_var, CompilerInfo & info, Scope & scope) {
		auto & global = resolve_static(global_var, info.global_table, scope);
		InstructionBuffer buf;
		buf << inst::global_write(global.id);
		return ExprResult{ buf };
	}



	ExprResult compile_read_static(const ast::DefinitionValue & def, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << inst::global_read(resolve_static(def, info.definition_table, scope).id);
		return ExprResult{ buf };
	}



	ExprResult compile_write_static(const ast::DefinitionValue & def, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << inst::global_write(resolve_static(def, info.definition_table, scope).id);
		return ExprResult{ buf };
	}
}