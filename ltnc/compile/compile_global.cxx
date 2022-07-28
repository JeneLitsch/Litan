#include "compile.hxx"
#include <sstream>
namespace ltn::c {
	namespace {
		auto undefined_global(const ast::GlobalVar & global) {
			std::ostringstream oss;
			oss
				<< "Undefined global variable "
				<< global.namespaze.to_string() << global.name;

			return CompilerError { oss.str(), global.location };
		}

		std::uint64_t resolve_address(const ast::GlobalVar & global, CompilerInfo & info, Scope & scope) {
			const auto global_var = info.global_table.resolve(
				global.name,
				scope.get_namespace(),
				global.namespaze);

			if(!global_var) throw undefined_global(global);
			return global_var->id;
		}
	}

	ExprCode compile_read_global(const ast::GlobalVar & global, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		buf << ltn::inst::GlobalRead { resolve_address(global, info, scope) };
		return ExprCode{ buf };
	}



	ExprCode compile_write_global(
		const ast::GlobalVar & global,
		CompilerInfo & info,
		Scope & scope) {
		
		InstructionBuffer buf;

		buf << ltn::inst::GlobalWrite{ resolve_address(global, info, scope) };
		return ExprCode{ buf };
	}
}