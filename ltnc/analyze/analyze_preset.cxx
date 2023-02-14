#include "analyze.hxx"

namespace ltn::c {
	namespace {
		ast::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = std::make_unique<ast::Call>(
				std::make_unique<ast::Var>("struct", Namespace{{"std"}}, loc),
				std::vector<ast::Expression>{},
				loc
			);
			
			return std::make_unique<ast::NewVar>(
				std::make_unique<ast::NewVarBinding>(loc, "___OBJ___"),
				std::move(call),
				loc
			);
		}



		ast::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = std::make_unique<ast::Var>("___OBJ___", Namespace{}, loc);
			return std::make_unique<ast::Return>(std::move(obj), loc);
		}
	}



	ast::func_ptr generate_ctor(const ast::Preset & preset) {
		ast::Parameters parameters;

		auto expr = ast::InitStruct{preset.location, {}};

		for(const auto & member : preset.members) {
			const auto var_name = "__" + member.name + "__";

			expr.members.push_back({
				member.name,
				ast::Var(var_name, Namespace{}, preset.location)
			});

			parameters.push_back(ast::Parameter {
				.name = var_name,
				.type = member.type,
			});
		}

		auto stmt = std::make_unique<ast::Return>(std::move(expr), preset.location);

		auto ctor = std::make_unique<ast::Function>(
			preset.name,
			preset.namespaze,
			parameters,
			std::move(stmt),
			type::IncompleteType{type::Any{}},
			preset.location
		);

		ctor->is_const = true;

		return ctor;
	}
}