#include "analyze.hxx"
#include "ltnc/sst/stmt/ForEach.hxx"
#include "ltnc/sst/stmt/InfiniteLoop.hxx"
#include "ltnc/sst/stmt/While.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::While & stmt, Scope & scope) {

		// outer scope of loop 
		MinorScope loop_scope { &scope }; 
		
		// compile parts
		auto condition = analyze_expression(*stmt.condition, scope);
		auto body = analyze_statement(*stmt.body, loop_scope);

		return std::make_unique<sst::While>(
			std::move(condition),
			std::move(body)
		);
	}



	sst::stmt_ptr analyze_stmt(const ast::InfiniteLoop & stmt, Scope & scope) {

		MinorScope loop_scope { &scope }; 		
		auto body = analyze_statement(*stmt.body, loop_scope);
		return std::make_unique<sst::InfiniteLoop>(std::move(body));
	}



	sst::stmt_ptr analyze_stmt(const ast::ForEach & stmt, Scope & scope) {
		MinorScope loop_scope { &scope };
		
		const auto label = make_jump_id("FOREACH");
		auto expr = analyze_expression(*stmt.expr, loop_scope);				
		const auto element_var = loop_scope.insert(stmt.index_name, location(stmt));
		const auto iterator_var = loop_scope.insert("_iterator_" + stmt.index_name, location(stmt));
		const auto container_var = loop_scope.insert("_container_" + stmt.index_name, location(stmt));
		auto body = analyze_statement(*stmt.body, loop_scope);

		return std::make_unique<sst::ForEach>(
			element_var.address,
			iterator_var.address,
			container_var.address,
			std::move(expr),
			std::move(body)
		);
	}
}