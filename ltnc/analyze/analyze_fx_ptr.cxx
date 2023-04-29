#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "stdxx/iife.hxx"
#include <string_view>

namespace ltn::c {
	namespace {

		struct ParamResult {
			type::Type type;
			std::optional<std::pair<std::string, type::Type>> deduced_type;
		};


		ParamResult analyze_parameter(
			const ast::Parameter::Infered & infered,
			const std::optional<ast::type_ptr> & declared,
			Scope & scope) {
			auto type = declared ? analyze_type(**declared, scope) : type::Any{};
			return ParamResult{
				.type = type,
				.deduced_type = std::make_pair(infered.name, type),
			}; 
		}



		ParamResult analyze_parameter(
			const ast::type_ptr & type,
			const std::optional<ast::type_ptr> & declared,
			Scope & scope) {
				
			auto t = analyze_type(*type, scope);
			return ParamResult{
				.type = t,
				.deduced_type = std::nullopt
			}; 
		}
	}



	sst::expr_ptr analyze_expr(const ast::FxPointer & fx_ptr, Scope & scope) {

		MinorScope inner_scope{&scope};

		std::map<std::string, type::Type> deduced_types;
		std::vector<type::Type> parameter_types;

		auto & context = scope.get_context();

		const auto fx = scope.resolve_function(
			fx_ptr.name,
			fx_ptr.namespaze,
			fx_ptr.arity()
		);

		if(!fx) throw undefined_function(fx_ptr);
		
		for(std::size_t i = 0; i < fx_ptr.arity(); ++i) {
			auto & param = fx->parameters[i];
			auto & arg = fx_ptr.placeholders[i];
			auto [type, deduced] = std::visit([&] (auto & p) {
				return analyze_parameter(p, arg, scope);
			}, param.type);
			if(deduced) {
				deduced_types.insert(*deduced);
			}
			parameter_types.push_back(type);
		}

		MinorScope param_scope{&inner_scope};

		param_scope.inherit_types(deduced_types);

		const auto return_type = analyze_type(*fx->return_type, scope);

		const auto type = type::FxPtr {
			.return_type = return_type,
			.parameter_types = parameter_types,
		};

		context.fx_queue.stage_function(Staged{
			.fx = *fx,
			.deduced_types = deduced_types,
			.captures = {},
			.override_namespace = std::nullopt,
		});

		const auto label = make_function_label(*fx, deduced_types);

		return std::make_unique<sst::FxPointer>(
			label,
			fx->parameters.size(),
			type
		);
	}
}