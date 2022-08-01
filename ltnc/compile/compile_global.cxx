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

		std::uint64_t resolve_address(const auto & statik, auto & table, Scope & scope) {
			const auto static_var = table.resolve(
				statik.name,
				scope.get_namespace(),
				statik.namespaze);

			if(!static_var) throw undefined(statik);
			return static_var->id;
		}
	}

	ExprCode compile_read_static(const ast::GlobalVar & global, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << ltn::inst::GlobalRead { resolve_address(global, info.global_table, scope) };
		return ExprCode{ buf };
	}



	ExprCode compile_write_static(const ast::GlobalVar & global, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << ltn::inst::GlobalWrite{ resolve_address(global, info.global_table, scope) };
		return ExprCode{ buf };
	}



	ExprCode compile_read_static(const ast::DefinitionValue & def, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << ltn::inst::GlobalRead { resolve_address(def, info.definition_table, scope) };
		return ExprCode{ buf };
	}



	ExprCode compile_write_static(const ast::DefinitionValue & def, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << ltn::inst::GlobalWrite{ resolve_address(def, info.definition_table, scope) };
		return ExprCode{ buf };
	}



}