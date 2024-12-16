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



		template<typename InstT>
		std::size_t get_inst_size(const InstT &) {
			return InstT::size;
		}

		std::size_t get_inst_size(const inst::InstUint64Bytex & inst) {
			return 1 + 8 + inst.bytes.size();
		}

		std::size_t get_inst_size(const inst::InstBytex0 & inst) {
			return 1 + inst.bytes.size() + 1;
		}

		std::size_t size(const inst::Inst & inst) {
			return std::visit([](auto & i) {
				return get_inst_size(i);
			}, inst);
		}

		AddressTable generate_jump_table(const std::vector<inst::Inst> & instructions) {
			std::size_t position = 0;
			AddressTable table;
			for(const auto & inst : instructions) {
				position += size(inst);
				if(auto label = std::get_if<inst::InstLabel>(&inst)) {
					if(table.contains(label->label)) throw std::runtime_error {
						"Redefinition of label " + std::string(label->label)
					};
					table.insert({label->label, position});
				}
			}
			return table;
		}

		StringPool generate_string_pool(const std::vector<inst::Inst> & instructions) {
			StringPool string_pool;
			for(const auto & inst : instructions) {
				if(auto inst_string_constant = std::get_if<inst::InstStringConstant>(&inst)) {
					string_pool.push(inst_string_constant->label);
				}
			}
			return string_pool;
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
		AddressTable jump_table = generate_jump_table(instructions);

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

		StringPool string_pool = generate_string_pool(instructions);

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
			.string_pool = string_pool,
		};
	}
}