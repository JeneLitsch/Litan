#include "compile.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	sst::stmt_ptr  analyze_stmt(const ast::Block & block, CompilerInfo & info, Scope & parent) {
		MinorScope scope { &parent };
		std::size_t locals = 0;
		std::size_t newAllocs = 0;
		std::vector<sst::stmt_ptr> statments;
		for(const auto & stmt : block.statements) {
			try {
				if(stmt) {
					auto analyzed = analyze_statement(*stmt, info, scope); 
					locals = std::max(locals, analyzed->local_vars);
					newAllocs += analyzed->direct_allocation;
					statments.push_back(std::move(analyzed));
				} 
			}
			catch(const CompilerError & error) {
				info.reporter.push(error);
			}
		}
		return std::make_unique<sst::Block>(
			locals + newAllocs,
			false,
			std::move(statments)
		);
	}
}
