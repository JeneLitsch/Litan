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

		auto undefined(const ast::Var & def) {
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

	sst::expr_ptr analyze_expr(
		const ast::GlobalVar & global_var,
		CompilerInfo & info,
		Scope & scope) {
		
		auto & global = resolve_static(global_var, info.global_table, scope);
		const auto type = instantiate_type(global.type, scope);

		InstructionBuffer buf;
		buf << inst::global_read(global.id);
		
		return sst::expr_ptr{ 
			.code = buf,
			.deduced_type = instantiate_type(global.type, scope),
		};
	}



	sst::expr_ptr analyze_write_global(
		const ast::GlobalVar & global_var,
		CompilerInfo & info,
		Scope & scope) {

		const auto & global = resolve_static(global_var, info.global_table, scope);
		const auto type = instantiate_type(global.type, scope);
		
		InstructionBuffer buf;
		buf << inst::global_write(global.id);

		return sst::expr_ptr{ 
			.code = buf,
			.deduced_type = type	
		};
	}



	sst::expr_ptr analyze_write_define(
		const ast::Var & def,
		CompilerInfo & info,
		Scope & scope) {

		InstructionBuffer buf;

		const auto & statik = resolve_static(def, info.definition_table, scope);
		const auto type = instantiate_type(statik.type, scope);
		
		buf << inst::global_write(statik.id);

		return sst::expr_ptr{ 
			.code = buf,
			.deduced_type = type,
		};
	}
}