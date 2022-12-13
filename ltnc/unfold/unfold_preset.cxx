#include "unfold.hxx"

namespace ltn::c {
	namespace {
		ast::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = stx::make_unique<ast::Call>(
				stx::make_unique<ast::Var>("struct", Namespace{{"std"}}, loc),
				std::vector<ast::expr_ptr>{},
				loc);
			
			return stx::make_unique<ast::NewVar>(
				"obj",
				std::move(call),
				loc);
		}



		ast::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = stx::make_unique<ast::Var>("obj", Namespace{}, loc);
			return stx::make_unique<ast::Return>(std::move(obj), loc);
		}
	}



	ast::func_ptr unfold_preset(ast::prst_ptr preset) {
		std::vector<ast::stmt_ptr> statements;
		ast::Parameters parameters;
		statements.push_back(new_struct(preset->location));

		for(const auto & member : preset->members) {
			const auto var_name = "__" + member.name + "__";
			
			auto init_member = stx::make_unique<ast::InitMember>(
				member.name,
				var_name,
				member.type,
				preset->location
			);

			statements.push_back(std::move(init_member));
			parameters.push_back(ast::Parameter{
				.name = var_name,
				.type = member.type,
			});
		}

		statements.push_back(return_struct(preset->location));
		
		auto block = stx::make_unique<ast::Block>(
			std::move(statements),
			preset->location);

		auto ctor = stx::make_unique<ast::Function>(
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