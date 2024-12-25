#include "analyze.hxx"
#include "litan_compiler/ast/stmt/Block.hxx"
#include "litan_compiler/sst/stmt/Block.hxx"

#include "litan_compiler/scoping/BlockScope.hxx"

namespace ltn::c {
	// compiles -> code block {...}
	sst::stmt_ptr  analyze_stmt(const ast::stmt::Block & block, Scope & parent) {
		
		BlockScope scope { &parent };

		std::vector<sst::stmt_ptr> statments;
		for(const auto & stmt : block.statements) {
			statments.push_back(analyze_statement(*stmt, scope));
		}
		return sst::stmt::block(std::move(statments));
	}
}
