#include "compile.hxx"

namespace ltn::c {
	namespace {
		sst::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = stx::make_unique<sst::Call>(
				stx::make_unique<sst::Var>("struct", Namespace{{"std"}}, loc),
				std::vector<sst::expr_ptr>{},
				loc);
			
			return stx::make_unique<sst::NewVar>(
				"obj",
				std::move(call),
				loc);
		}



		sst::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = stx::make_unique<sst::Var>("obj", Namespace{}, loc);
			return stx::make_unique<sst::Return>(std::move(obj), loc);
		}
	}



	sst::func_ptr analyze_preset(const ast::Preset & preset) {
		std::vector<sst::stmt_ptr> statements;
		sst::Parameters parameters;
		statements.push_back(new_struct(preset.location));

		for(const auto & member : preset.members) {
			const auto var_name = "__" + member.name + "__";
			
			auto init_member = stx::make_unique<sst::InitMember>(
				member.name,
				var_name,
				member.type,
				preset.location
			);

			statements.push_back(std::move(init_member));
			parameters.push_back(sst::Parameter{
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