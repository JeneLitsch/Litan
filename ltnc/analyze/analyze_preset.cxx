#include "analyze.hxx"

namespace ltn::c {
	ast::func_ptr generate_ctor(const ast::Preset & preset) {
		ast::Parameters parameters;

		auto expr = std::make_unique<ast::InitStruct>(location(preset));

		// for(const auto & member : preset.members) {
		// 	const auto var_name = "__" + member.name + "__";

		// 	expr->members.push_back({
		// 		member.name,
		// 		std::make_unique<ast::Var>(var_name, Namespace{}, location(preset))
		// 	});

		// 	parameters.push_back(ast::Parameter {
		// 		.name = var_name,
		// 		.type = member.type,
		// 	});
		// }

		auto stmt = std::make_unique<ast::Return>(std::move(expr), location(preset));

		auto ctor = std::make_unique<ast::Function>(
			preset.name,
			preset.namespaze,
			std::move(parameters),
			std::move(stmt),
			location(preset)
		);

		ctor->is_const = true;

		return ctor;
	}
}