#include "compile.hxx"

namespace ltn::c {
	namespace {
		sst::stmt_ptr new_struct(const SourceLocation & loc) {
			auto call = std::make_unique<sst::Call>(
				"std::struct(0)",
				std::vector<sst::expr_ptr>{},
				type::Any{}
			);
			
			return std::make_unique<sst::NewVar>(0, false, 0, std::move(call));
		}



		sst::stmt_ptr return_struct(const SourceLocation & loc) {
			auto obj = std::make_unique<sst::Var>(0, type::Any{});
			return std::make_unique<sst::Return>(0, false, std::move(obj), std::nullopt);
		}
	}



	sst::func_ptr analyze_preset(
		const ast::Preset & preset,
		CompilerInfo & info) {
		std::vector<sst::stmt_ptr> statements;
		sst::Parameters parameters;
		statements.push_back(new_struct(preset.location));

		FunctionScope scope{preset.namespaze, false};

		for(const auto & member : preset.members) {
			const auto var_name = "__" + member.name + "__";
			const auto type = instantiate_type(member.type, scope);
			const auto var = scope.insert(var_name, preset.location, type);

			auto init_member = std::make_unique<sst::InitMember>(
				0, false,
				0,
				info.member_table.get_id(var_name),
				var.address,
				instantiate_type(member.type, scope)
			);

			statements.push_back(std::move(init_member));
			parameters.push_back(sst::Parameter {
				.name = var_name,
				.type = instantiate_type(member.type, scope),
			});
		}

		statements.push_back(return_struct(preset.location));
		
		auto block = std::make_unique<sst::Block>(
			1, false,
			std::move(statements)
		);

		auto ctor = std::make_unique<sst::Function>(
			sst::mangle(preset.name, preset.namespaze, parameters),
			preset.name,
			preset.namespaze,
			parameters,
			std::move(block),
			type::Any{}
		);

		ctor->c0nst = true;

		return ctor;
	}
}