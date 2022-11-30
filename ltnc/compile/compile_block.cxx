#include "compile.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	StmtResult compile_stmt(const ast::Block & block, CompilerInfo & info, Scope & parent) {
		MinorScope scope { &parent };
		InstructionBuffer buf;
		std::size_t locals = 0;
		std::size_t newAllocs = 0;
		for(const auto & stmt : block.statements) {
			try {
				if(stmt) {
					const auto compiled = compile_statement(*stmt, info, scope); 
					buf << compiled.code;
					locals = std::max(locals, compiled.var_count);
					newAllocs += compiled.direct_allocation;
				} 
			}
			catch(const CompilerError & error) {
				info.reporter.push(error);
			}
		}
		return { buf, locals + newAllocs, false };
	}
}
