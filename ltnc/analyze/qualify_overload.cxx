#include "qualify_overload.hxx"
#include "analyze.hxx"

namespace ltn::c {
	namespace {
		bool matches_strict(
			const ast::Functional & function,
			const std::vector<sst::expr_ptr> & arguments,
			const Scope & scope) {
			
			for(std::size_t i = 0; i < function.parameters.size(); ++i) {
				auto param_type = instantiate_type(
					function.parameters[i].type,
					scope
				);
				if(arguments[i]->type != param_type) {
					return false;
				}
			}

			return true;
		}
	}



	const ast::Functional * qualify_overload(
		const ast::Overload & overload,
		const FunctionTable & fx_table,
		const std::vector<sst::expr_ptr> & arguments,
		const Scope & scope) {
		
		for(const auto & element : overload.elements) {
			auto * fx = fx_table.resolve(
				element.name,
				overload.namespaze,
				element.namespaze,
				overload.arity
			);

			if(!fx) {
				throw undefined_function(overload.name, overload);
			}

			if(matches_strict(*fx, arguments, scope)) return fx;

		}

		return nullptr;
	}
}