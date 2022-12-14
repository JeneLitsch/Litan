#include "stdxx/functional.hxx"
#include "compile.hxx"

namespace ltn::c {
	void add_template_args(
		Scope & scope,
		const std::vector<std::string> & template_params,
		const std::vector<type::IncompleteType> & template_args) {
		const auto arguments = stx::fx::map(instantiate_type, template_args, scope);
		return add_template_args(scope, template_params, arguments);
	}


	void add_template_args(
		Scope & scope,
		const std::vector<std::string> & template_params,
		const std::vector<type::Type> & template_args) {
		for(std::size_t i = 0; i < template_args.size(); ++i) {
			scope.add_type(template_params[i], template_args[i]);
		}
	}


	std::string make_template_id(
		const sst::Functional & fx,
		const std::vector<type::Type> & arguments) {
		
		std::ostringstream oss;
		oss << "<";
		oss << fx.get_resolve_namespace().to_string();
		oss << fx.get_resolve_name();
		oss << ":";
		bool first = true;
		for(const auto & arg : arguments) {
			if(first) {
				first = false;
			}
			else {
				oss << ",";
			}
			oss << type::to_string(arg);
		} 
		oss << ">"; 
		oss << "(" << fx.parameters.size() << ")";
		return oss.str();
	}
}