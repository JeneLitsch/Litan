#include "analyze.hxx"

#include "litan_compiler/ast/bind/Group.hxx"
#include "litan_compiler/ast/bind/NewVar.hxx"

#include "litan_compiler/sst/expr/Var.hxx"
#include "litan_compiler/sst/bind/Group.hxx"
#include "litan_compiler/sst/bind/NewVar.hxx"

namespace ltn::c {
	sst::bind_ptr analyze_bind(const ast::bind::Group & binding, Scope & scope) {

		auto sst_binding = sst::bind::group();

		for(std::size_t i = 0; i < std::size(binding.sub_bindings); ++i) {
			auto sub_binding = analyze_binding(*binding.sub_bindings[i], scope);
			sst_binding->sub_bindings.push_back(std::move(sub_binding));
		}

		return sst_binding;
	}
	

	
	sst::bind_ptr analyze_bind(const ast::bind::NewVar & binding, Scope & scope) {
		const auto var = scope.declare_variable(binding.name, ast::location(binding)); 
		return sst::bind::new_local(var.address);
	}



	sst::bind_ptr analyze_binding(const ast::bind::Binding & binding, Scope & scope) {
		
		auto fx = [&] (const auto & b) {
			return analyze_bind(b, scope);
		};

		return ast::bind::visit(binding, fx);
	}
}