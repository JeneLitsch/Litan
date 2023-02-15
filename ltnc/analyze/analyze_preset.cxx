#include "analyze.hxx"

namespace ltn::c {
	ast::func_ptr generate_ctor(const ast::Preset & preset) {
		ast::Parameters parameters;

		auto init = ast::InitStruct(preset.location);

		for(const auto & member : preset.members) {
			const auto var_name = "__" + member.name + "__";

			init.members.push_back(ast::InitStruct::Member{
				member.name,
				ast::Expression{ast::Var(var_name, Namespace{}, preset.location)}
			});

			parameters.push_back(ast::Parameter {
				.name = var_name,
				.type = member.type,
			});
		}

		auto stmt = std::make_unique<ast::Return>(std::move(init), preset.location);

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