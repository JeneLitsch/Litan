#include "analyze.hxx"
#include "ltnc/sst/stmt/Block.hxx"
namespace ltn::c {
	// compiles -> code block {...}
	sst::stmt_ptr  analyze_stmt(const ast::stmt::Block & block, Scope & parent) {
		
		MinorScope scope { &parent };

		std::vector<sst::stmt_ptr> statments;
		for(const auto & stmt : block.statements) {
			statments.push_back(analyze_statement(*stmt, scope));
		}
		return sst::stmt::block(std::move(statments));
	}
}
