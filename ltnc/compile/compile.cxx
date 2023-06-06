#include "stdxx/functional.hxx"
#include "compile.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer static_init(auto & statics) {
			InstructionBuffer buf;
			for(const auto & s : statics) {
				if(s->expr) {
					buf << compile_expression(*s->expr);
				}
			}
			return buf;
		}
	}



	// compiles source
	std::tuple<std::vector<inst::Inst>, LinkInfo> compile(
		const sst::Program & program,
		Reporter &) {
		
		InstructionBuffer buf;

		buf << static_init(program.definitions);
		buf << static_init(program.globals);

		buf << inst::null();
		buf << inst::exit();
		
		for(const auto & function : program.functions) {
			buf << compile_functional(*function);
		}

		std::set<std::string> extern_functions;
		extern_functions.insert("main(0)");
		extern_functions.insert("main(1)");
		for(const auto & fx : program.functions) {
			if(fx->is_extern) extern_functions.insert(fx->label.to_string());
		}

		AddressTable extern_globals;
		for(const auto & symbol : program.globals) {
			const auto full_name = symbol->namespaze.to_string() + symbol->name;
			extern_globals.insert({full_name, symbol->id});
		}

		std::map<std::uint64_t, std::string> member_name_table;

		buf << inst::exit();

		return { buf.get(), LinkInfo { 
			.init_functions = extern_functions,
			.global_table = extern_globals,
			.member_name_table = program.member_name_table,
		}};
	}
}