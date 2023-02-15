#include "analyze.hxx"

namespace ltn::c {
	namespace {
		std::string var_from(const std::string & name) {
			return name + "_FROM";
		}

		std::string var_to(const std::string & name) {
			return name + "_TO";
		}
	}

	sst::stmt_ptr analyze_stmt(
		const ast::While & stmt,
		Context & context,
		Scope & scope) {

		// outer scope of loop 
		MinorScope loop_scope { &scope }; 
		
		// compile parts
		auto condition = analyze_expression(stmt.condition, context, scope);
		auto body = analyze_statement(*stmt.body, context, loop_scope);

		return std::make_unique<sst::While>(
			std::move(condition),
			std::move(body)
		);
	}



	sst::stmt_ptr analyze_stmt(
		const ast::InfiniteLoop & stmt,
		Context & context,
		Scope & scope) {

		MinorScope loop_scope { &scope }; 		
		auto body = analyze_statement(*stmt.body, context, loop_scope);
		return std::make_unique<sst::InfiniteLoop>(std::move(body));
	}



	sst::stmt_ptr analyze_stmt(
		const ast::For & stmt,
		Context & context,
		Scope & scope) {
		
		// outer scope of loop 
		MinorScope loop_scope { &scope };

		auto from = analyze_expression(stmt.from, context, loop_scope);
		auto to = analyze_expression(stmt.to, context, loop_scope);
		auto step = stmt.step
			? analyze_expression(stmt.step, context, scope)
			: std::make_unique<sst::Integer>(1, type::Int{});
		
		const auto label = make_jump_id("FOR");

		const auto i_var = loop_scope.insert(stmt.index_name, location(stmt), type::Int{});
		loop_scope.insert(var_from(label), location(stmt));
		loop_scope.insert(var_to(label), location(stmt));

		auto body = analyze_statement(*stmt.body, context, loop_scope);
				
		return std::make_unique<sst::For>(
			label,
			i_var.address,
			std::move(from),
			std::move(to),
			std::move(step),
			std::move(body)
		);
	}



	sst::stmt_ptr analyze_stmt(
		const ast::ForEach & stmt,
		Context & context,
		Scope & scope) {
		MinorScope loop_scope { &scope };
		
		const auto label = make_jump_id("FOREACH");
		const auto element_var = loop_scope.insert(stmt.index_name, location(stmt), type::Int{});
		const auto iterator_var = loop_scope.insert("_iterator_" + stmt.index_name, location(stmt), type::Any{});
		const auto container_var = loop_scope.insert("_container_" + stmt.index_name, location(stmt), type::Any{});
		auto expr = analyze_expression(stmt.expr, context, loop_scope);				
		auto body = analyze_statement(*stmt.body, context, loop_scope);

		return std::make_unique<sst::ForEach>(
			element_var.address,
			iterator_var.address,
			container_var.address,
			std::move(expr),
			std::move(body)
		);
	}
}