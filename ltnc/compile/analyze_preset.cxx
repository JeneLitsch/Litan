#include "compile.hxx"

namespace ltn::c {
	namespace {
		sst::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = stx::make_unique<sst::Call>(
				stx::make_unique<sst::Var>("struct", Namespace{{"std"}}, loc),
				std::vector<sst::expr_ptr>{},
				loc);
			
			return std::make_unique<sst::NewVar>(
				"obj"
				std::move(call),
				loc);
		}



		sst::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = stx::make_unique<sst::Var>("obj", Namespace{}, loc);
			return stx::make_unique<sst::Return>(std::move(obj), loc);
		}
	}



	sst::func_ptr analyze_preset(
		const ast::Preset & preset,
		CompilerInfo & info,
		Scope & scope) {
		std::vector<sst::stmt_ptr> statements;
		sst::Parameters parameters;
		statements.push_back(new_struct(preset.location));

		for(const auto & member : preset.members) {
			const auto var_name = "__" + member.name + "__";
			const auto var = scope.insert(var_name, preset.location, member.type);

			auto init_member = std::make_unique<sst::InitMember>(
				0, false,
				0,
				info.member_table.get_id(var_name),
				var.address,
				member.type
			);

			statements.push_back(std::move(init_member));
			parameters.push_back(sst::Parameter {
				.name = var_name,
				.type = member.type,
			});
		}

		statements.push_back(return_struct(preset.location));
		
		auto block = stx::make_unique<sst::Block>(
			std::move(statements),
			preset.location);

		auto ctor = stx::make_unique<sst::Function>(
			preset.name,
			preset.namespaze,
			parameters,
			std::move(block),
			preset.location
		);

		ctor->c0nst = true;

		return ctor;
	}
}