#include "analyze.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	sst::stmt_ptr  analyze_stmt(
		const ast::Block & block,
		Context & context,
		Scope & parent) {
		
		MinorScope scope { &parent };
		std::size_t locals = 0;
		std::size_t newAllocs = 0;
		std::vector<sst::stmt_ptr> statments;
		for(const auto & stmt : block.statements) {
			try {
				if(stmt) {
					auto analyzed = analyze_statement(*stmt, context, scope); 
					locals = std::max(locals, analyzed->nested_alloc());
					newAllocs += analyzed->direct_alloc();
					statments.push_back(std::move(analyzed));
				} 
			}
			catch(const CompilerError & error) {
				context.reporter.push(error);
			}
		}
		return std::make_unique<sst::Block>(
			locals + newAllocs,
			false,
			std::move(statments)
		);
	}
}
