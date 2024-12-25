#include "stdxx/functional.hxx"
#include "compile.hxx"
#include "peephole/peephole.hxx"
#include "link/link.hxx"

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
	inst::Program compile(const sst::Program & program, const CompileOptions & options) {
		
		InstructionBuffer buf;

		buf << static_init(program.definitions);
		buf << static_init(program.globals);

		buf << inst::null();
		buf << inst::exit();
		
		for(const auto & function : program.functions) {
			buf << compile_function(*function);
		}

		buf << inst::exit();

		auto instructions = options.optimize ? ltn::c::peephole(buf.get()) : buf.get();
		auto link_info = ltn::c::link(program, instructions);

		return {
			.instructions = std::move(instructions),
			.link_info = link_info,
		};
	}
}