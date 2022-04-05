#include "compile.hxx"
namespace ltn::c::compile {
	// compiles -> code block {...}
	StmtCode block(const ast::Block & block, CompilerInfo & info, Scope & parent) {
		Scope scope(&parent);
		std::stringstream ss;
		std::size_t locals = 0;
		std::size_t newAllocs = 0;
		for(const auto & stmt : block.statements) {
			try {
				if(stmt) {
					const auto compiled = compile::statement(*stmt, info, scope); 
					ss << compiled.code;
					locals = std::max(locals, compiled.var_count);
					newAllocs += compiled.direct_allocation;
				} 
			}
			catch(const CompilerError & error) {
				info.reporter.push(error);
			}
		}
		return {ss.str(), locals + newAllocs, false};
	}
}