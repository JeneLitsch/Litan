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


	stx::reference<const ast::FunctionTemplate> get_template(
		const std::string & name,
		const ast::Namespace & namespaze,
		const std::size_t function_arity,
		const std::size_t template_arity,
		const SourceLocation & location,
		CompilerInfo & info,
		Scope & scope) {
		const auto * tmpl = info.fx_template_table.resolve(
			name,
			scope.get_namespace(),
			namespaze,
			function_arity,
			template_arity
		);
		if(!tmpl) {
			std::ostringstream oss;
			oss 
				<< "Cannot find template " 
				<< namespaze.to_string() << name
				<< " with " << template_arity << " arguements";
			throw CompilerError{oss.str(), location};
		}
		return *tmpl;
	}



	std::string make_template_id(
		const ast::Functional & fx,
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