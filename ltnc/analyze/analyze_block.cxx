#include "analyze.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	sst::stmt_ptr  analyze_stmt(const ast::Block & block, Scope & parent) {
		
		MinorScope scope { &parent };

		std::vector<sst::stmt_ptr> statments;
		for(const auto & stmt : block.statements) {
			try {
				statments.push_back(analyze_statement(*stmt, scope));
			}
			catch(const CompilerError & error) {
				scope.get_context().reporter.push(error);
			}
		}
		return std::make_unique<sst::Block>(std::move(statments));
	}
}
