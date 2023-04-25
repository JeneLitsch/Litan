#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	namespace {
		type::Type analyze_argument_type_impl(const type::IncompleteType & type, Scope & scope) {
			return instantiate_type(type, scope);
		}



		type::Type analyze_argument_type_impl(const ast::Parameter::Infered & infered, Scope & scope) {
			auto * type = scope.resolve_type(infered.name);
			if(type) return *type;
			throw CompilerError { "Undeclared type: " + infered.name };
		}
	}



	type::Type analyze_parameter_type(const ast::Parameter::DeclType & type, Scope & scope) {
		return std::visit([&] (const auto & t) {
			return analyze_argument_type_impl(t, scope);
		}, type);
	}
}