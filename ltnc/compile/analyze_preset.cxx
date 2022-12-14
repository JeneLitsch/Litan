#include "compile.hxx"

namespace ltn::c {
	namespace {
		ast::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = std::make_unique<ast::Call>(
				std::make_unique<ast::Var>("struct", Namespace{{"std"}}, loc),
				std::vector<ast::expr_ptr>{},
				loc
			);
			
			return std::make_unique<ast::NewVar>("___OBJ___", std::move(call), loc);
		}



		ast::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = std::make_unique<ast::Var>("___OBJ___", Namespace{}, loc);
			return std::make_unique<ast::Return>(std::move(obj), loc);
		}
	}



	ast::func_ptr generate_ctor(const ast::Preset & preset) {
		std::vector<ast::stmt_ptr> statements;
		ast::Parameters parameters;
		statements.push_back(new_struct(preset.location));

		FunctionScope scope{preset.namespaze, false};

		for(const auto & member : preset.members) {
			const auto var_name = "__" + member.name + "__";
			const auto type = instantiate_type(member.type, scope);
			const auto var = scope.insert(var_name, preset.location, type);

			auto init_member = std::make_unique<ast::InitMember>(
				member.name,
				var_name,
				member.type,
				preset.location
			);

			statements.push_back(std::move(init_member));
			parameters.push_back(ast::Parameter {
				.name = var_name,
				.type = member.type,
			});
		}

		statements.push_back(return_struct(preset.location));
		
		auto block = std::make_unique<ast::Block>(std::move(statements), preset.location);

		auto ctor = std::make_unique<ast::Function>(
			preset.name,
			preset.namespaze,
			parameters,
			std::move(block),
			type::IncompleteType{type::Any{}},
			preset.location
		);

		ctor->c0nst = true;

		return ctor;
	}
}