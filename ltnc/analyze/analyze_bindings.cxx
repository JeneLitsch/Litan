#include "analyze.hxx"
#include "ltnc/type/traits.hxx"

namespace ltn::c {
	namespace {
		sst::bind_ptr analyze_bind(
			const ast::GroupBinding & binding,
			Scope & scope,
			const type::Type & from_type) {

			if(!type::is_tuple(from_type)) {
				throw cannot_unpack_tuple(binding);
			} 
			
			auto sst_binding = std::make_unique<sst::GroupBinding>();

			for(std::size_t i = 0; i < std::size(binding.sub_bindings); ++i) {
				auto type = type::deduce_index(from_type, type::Int{}, i);
				if(type::is_error(type)) {
					throw cannot_unpack_tuple(binding);
				} 
				auto sub_binding = analyze_binding(*binding.sub_bindings[i], scope, type);
				sst_binding->sub_bindings.push_back(std::move(sub_binding));
			}

			return sst_binding;
		}
		

		
		sst::bind_ptr analyze_bind(
			const ast::NewVarBinding & binding,
			Scope & scope,
			const type::Type & from_type) {

			const auto var = scope.insert(binding.name, location(binding), from_type); 
			return std::make_unique<sst::NewVarBinding>(var.address);
		}
	}



	sst::bind_ptr analyze_binding(
		const ast::Binding & binding,
		Scope & scope,
		const type::Type & from_type) {

		return ast::visit_binding(binding, [&] (const auto & b) {
			return analyze_bind(b, scope, from_type);
		});
	}
}