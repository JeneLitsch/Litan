#include "analyze.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	sst::stmt_ptr  analyze_stmt(
		const ast::Block & block,
		Context & context,
		Scope & parent) {
		
		MinorScope scope { &parent };

		std::vector<sst::stmt_ptr> statments;
		for(const auto & stmt : block.statements) {
			try {
				statments.push_back(analyze_statement(*stmt, context, scope));
			}
			catch(const CompilerError & error) {
				context.reporter.push(error);
			}
		}
		return std::make_unique<sst::Block>(std::move(statments));
	}
}
