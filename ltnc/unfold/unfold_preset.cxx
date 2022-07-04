#include "unfold.hxx"

namespace ltn::c {
	namespace {
		ast::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = std::make_unique<ast::Call>(
				"struct",
				ast::Namespace{{"std"}},
				std::vector<ast::expr_ptr>{},
				loc);
			
			return std::make_unique<ast::NewVar>(
				"obj",
				std::move(call),
				loc);
		}



		ast::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = std::make_unique<ast::Var>("obj", loc);
			return std::make_unique<ast::Return>(std::move(obj), loc);
		}
	}



	ast::func_ptr unfold_preset(ast::prst_ptr preset) {
		std::vector<ast::stmt_ptr> statements;
		ast::Parameters parameters;
		statements.push_back(new_struct(preset->location));

		for(const auto & member_name : preset->member_names) {
			const auto var_name = "__" + member_name + "__";
			
			auto init_member = std::make_unique<ast::InitMember>(
				member_name,
				var_name,
				preset->location);

			statements.push_back(std::move(init_member));
			parameters.push_back(var_name);
		}

		statements.push_back(return_struct(preset->location));
		
		auto block = std::make_unique<ast::Block>(
			std::move(statements),
			preset->location);

		auto ctor = std::make_unique<ast::Function>(
			preset->name,
			preset->namespaze,
			parameters,
			std::move(block),
			preset->location
		);

		ctor->c0nst = true;

		return ctor;
	}
}