#include "labels.hxx"
#include <sstream>
#include "ltnc/type/to_string.hxx"

namespace ltn::c {
	namespace {
		std::uint64_t unique_number() {
			static std::uint64_t counter = 0; 
			return counter++;
		}



	}



	Label make_internal_label(const std::string & name) {
		return Label { Label::UseCase::INTERNAL, name };
	}



	Label make_external_label(const std::string & name) {
		return Label { Label::UseCase::EXTERNAL, name };
	}



	Label make_lambda_label(
		const ast::Lambda &) {
		std::ostringstream oss;
		oss << "LAMBDA" << unique_number();
		return make_internal_label(oss.str());
	}



	Label make_function_label(const ast::Functional & fx) {
		std::ostringstream oss;
		oss << fx.get_resolve_namespace().to_string() 
			<< fx.get_resolve_name() 
			<< "(" 
			<< fx.parameters.size()
			<< ")";
		return make_external_label(oss.str());
	}


	Label make_function_label(
		const ast::Functional & fx,
		const std::map<std::string, type::Type> & args) {
		
		std::ostringstream oss;
		oss << fx.get_resolve_namespace().to_string() 
			<< fx.get_resolve_name() 
			<< "(" 
			<< fx.parameters.size()
			<< ")";

		bool first = true;
		for(const auto & [name, type] : args) {
			if(first) {
				oss << "{";
				first = false;
			}
			else {
				oss << ",";
			}
			oss << name << "=" << type::to_string(type);
		}
		if(!first) {
			oss << "}";
		}
		return make_external_label(oss.str());
	}



	Label derive_skip(const Label & label) {
		return make_internal_label(label.get_name() + "_SKIP");
	}



	Label derive_except(const Label & label) {
		return make_internal_label(label.get_name() + "_EXCEPT");
	}



	Label derive_template(const Label & label, const std::map<std::string, type::Type> & args) {
		std::ostringstream oss;
		oss << label.get_name();
		for(const auto & [name, type] : args) {
			oss << "_" << name << "=" << type::to_string(type);
		}
		return make_internal_label(oss.str());
	}
}