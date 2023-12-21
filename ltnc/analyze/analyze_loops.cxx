#include "analyze.hxx"

#include "ltnc/ast/stmt/ForEach.hxx"
#include "ltnc/ast/stmt/InfiniteLoop.hxx"
#include "ltnc/ast/stmt/While.hxx"

#include "ltnc/sst/stmt/ForEach.hxx"
#include "ltnc/sst/stmt/InfiniteLoop.hxx"
#include "ltnc/sst/stmt/While.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::While & stmt, Scope & scope) {

		// outer scope of loop 
		MinorScope loop_scope { &scope }; 
		
		// compile parts
		auto condition = analyze_expression(*stmt.condition, scope);
		auto body = analyze_statement(*stmt.body, loop_scope);

		return sst::stmt::wh1le(
			std::move(condition),
			std::move(body)
		);
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::InfiniteLoop & stmt, Scope & scope) {
		MinorScope loop_scope { &scope }; 		
		
		auto body = analyze_statement(*stmt.body, loop_scope);
		return sst::stmt::infinite_loop(std::move(body));
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::ForEach & stmt, Scope & scope) {
		MinorScope loop_scope { &scope };
		
		auto expr = analyze_expression(*stmt.expr, loop_scope );
		auto bind = analyze_binding(*stmt.bind, loop_scope );
		
		const auto label = make_jump_id("FOREACH");
		const auto iterator_var = loop_scope.declare_variable("_iterator_" + label, location(stmt));
		const auto container_var = loop_scope.declare_variable("_container_" + label, location(stmt));
		
		auto body = analyze_statement(*stmt.body, loop_scope);

		return sst::stmt::for_each(
			std::move(bind),
			iterator_var.address,
			container_var.address,
			std::move(expr),
			std::move(body)
		);
	}
}