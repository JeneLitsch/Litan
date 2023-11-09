#pragma once
#include "ltnc/sst/SST.hxx"
namespace ltn::c {
	struct OptimizerInfo {
		
	};

	sst::expr_ptr optimize_unary(sst::expr::Unary & unary);
	sst::expr_ptr optimize_binary(sst::expr::Binary & binary);
	sst::expr_ptr optimize_ternary(sst::expr::Ternary & ternary);
	sst::expr_ptr optimize_expression(sst::expr::Expression & expr);
	sst::expr_ptr optimize_expression(sst::expr_ptr expr);

	sst::stmt_ptr optimize_statement(sst::Statement & stmt);
	sst::stmt_ptr optimize_statement(sst::stmt_ptr stmt);

	void optimize_definition(sst::Definition & definition);
	void optimize_function(sst::Function & function);


	void optimize(sst::Program & program);

}