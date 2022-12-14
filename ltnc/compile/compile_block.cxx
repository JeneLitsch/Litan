#include "compile.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	InstructionBuffer compile_stmt(const sst::Block & block, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		for(const auto & stmt : block.statements) {
			buf << compile_statement(*stmt, info, scope); 
		}
		return buf;
	}
}
