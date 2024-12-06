#include "stdxx/functional.hxx"
#include "compile.hxx"
#include "scan.hxx"

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
	std::vector<inst::Inst> compile(const sst::Program & program) {
		
		InstructionBuffer buf;

		buf << static_init(program.definitions);
		buf << static_init(program.globals);

		buf << inst::null();
		buf << inst::exit();
		
		for(const auto & function : program.functions) {
			buf << compile_function(*function);
		}

		buf << inst::exit();
		return buf.get();
	}



	LinkInfo link(const sst::Program & program, const std::vector<inst::Inst> & instructions) {
		AddressTable jump_table = scan(instructions);

		FunctionPool function_pool;
		for(const auto & fx : program.functions) {
			function_pool.push_back(FunctionContext {
				.name = fx->label.to_string(),
				.arity = fx->arity,
				.address = jump_table.at(fx->label.to_string()),
				.frame_size = fx->body->total_alloc(),
				.is_external = fx->qualifiers.is_extern,
				.is_variadic = fx->is_variadic,
			});
		}

		AddressTable extern_globals;
		for(const auto & symbol : program.globals) {
			if(symbol->is_extern) {
				const auto full_name = symbol->namespaze.to_string() + symbol->name;
				extern_globals.insert({full_name, symbol->id});
			}
		}

		return LinkInfo { 
			.global_table = extern_globals,
			.member_name_table = program.member_name_table,
			.jump_table = jump_table,
			.function_pool = function_pool,
		};
	}
}