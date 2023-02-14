#include "analyze.hxx"
#include "ltnc/type/traits.hxx"

namespace ltn::c {
	namespace {
		sst::bind_ptr analyze_bind(
			const ast::GroupBinding & binding,
			Context & context,
			Scope & scope,
			const type::Type & from_type) {

			if(!type::is_tuple(from_type)) throw CompilerError {
				"Can only unpack tuple",
				location(binding)
			};
			
			auto sst_binding = std::make_unique<sst::GroupBinding>();
			for(std::size_t i = 0; i < std::size(binding.sub_bindings); ++i) {
				auto type = type::deduce_index(from_type, type::Int{}, i);
				if(type::is_error(type)) throw CompilerError {
					"Cannot unpack tuple element",
					location(binding)
				};
				auto sub_binding = analyze_binding(*binding.sub_bindings[i], context, scope, type);
				sst_binding->sub_bindings.push_back(std::move(sub_binding));
			}

			return sst_binding;
		}
		

		
		sst::bind_ptr analyze_bind(
			const ast::NewVarBinding & binding,
			Context & context,
			Scope & scope,
			const type::Type & from_type) {

			const auto var = scope.insert(binding.name, location(binding), from_type); 
			return std::make_unique<sst::NewVarBinding>(var.address);
		}
	}



	sst::bind_ptr analyze_binding(
		const ast::Binding & binding,
		Context & context,
		Scope & scope,
		const type::Type & from_type) {

		return ast::visit_binding(binding, [&] (const auto & b) {
			return analyze_bind(b, context, scope, from_type);
		});
	}
}