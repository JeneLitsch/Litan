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
}