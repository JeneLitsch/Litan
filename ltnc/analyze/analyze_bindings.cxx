#include "analyze.hxx"
#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {
	namespace {
		sst::bind_ptr analyze_bind(
			const ast::GroupBinding & binding,
			Scope & scope) {

			auto sst_binding = std::make_unique<sst::bind::Group>();

			for(std::size_t i = 0; i < std::size(binding.sub_bindings); ++i) {
				auto sub_binding = analyze_binding(*binding.sub_bindings[i], scope);
				sst_binding->sub_bindings.push_back(std::move(sub_binding));
			}

			return sst_binding;
		}
		

		
		sst::bind_ptr analyze_bind(
			const ast::NewVarBinding & binding,
			Scope & scope) {

			const auto var = scope.insert(binding.name, location(binding)); 
			return std::make_unique<sst::bind::NewVar>(var.address);
		}
	}



	sst::bind_ptr analyze_binding(
		const ast::Binding & binding,
		Scope & scope) {

		return ast::visit_binding(binding, [&] (const auto & b) {
			return analyze_bind(b, scope);
		});
	}
}