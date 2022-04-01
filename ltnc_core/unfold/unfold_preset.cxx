#include "unfold.hxx"

namespace ltn::c::unfold {
	namespace {
		const ast::Namespace namespace_std {"std"};
		const std::string fx_struct = "struct";
		const std::string obj_name = "obj";
	}


	ast::expr_ptr obj_var(const SourceLocation & loc) {
		return std::make_unique<ast::Var>(obj_name, loc);
	}


	ast::stmt_ptr new_struct(const SourceLocation & loc) {
		auto call = std::make_unique<ast::Call>(
			fx_struct,
			namespace_std,
			std::vector<ast::expr_ptr>{},
			loc);
		
		return std::make_unique<ast::NewVar>(
			obj_name,
			std::move(call),
			loc);
	}



	ast::stmt_ptr return_struct(const SourceLocation & loc) {
		return std::make_unique<ast::Return>(obj_var(loc), loc);
	}



	ast::stmt_ptr write_member(
		const SourceLocation & loc,
		const std::string & member_name,
		const std::string & var_name) {
		
		auto l = std::make_unique<ast::Member>(
			obj_var(loc),
			member_name,
			loc);
		
		auto r = std::make_unique<ast::Var>(
			var_name,
			loc);
		
		auto assign = std::make_unique<ast::Assign>(
			std::move(l),
			std::move(r),
			loc);

		return std::make_unique<ast::StatementExpression>(
			std::move(assign),
			loc);
	}



	ast::func_ptr preset(ast::prst_ptr preset) {
		std::vector<ast::stmt_ptr> statements;
		ast::Parameters parameters;
		statements.push_back(new_struct(preset->location));

		for(const auto & member_name : preset->member_names) {
			const auto var_name = preset->name + "_" + member_name;
			auto stmt = write_member(preset->location, member_name, var_name);
			statements.push_back(std::move(stmt));
			parameters.push_back(var_name);
		}

		statements.push_back(return_struct(preset->location));
		
		auto block = std::make_unique<ast::Block>(
			std::move(statements),
			preset->location);

		return std::make_unique<ast::Function>(
			preset->name,
			preset->namespaze,
			parameters,
			std::move(block),
			preset->location
		);
	}
}