#include "compile.hxx"
#include "litan_compiler/sst/stmt/Block.hxx"

namespace ltn::c {
	// compiles -> code block {...}
	InstructionBuffer compile_stmt(const sst::stmt::Block & block) {
		InstructionBuffer buf;
		for(const auto & stmt : block.statements) {
			buf << compile_statement(*stmt); 
		}
		return buf;
	}
}
