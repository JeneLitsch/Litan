#include "labels.hxx"
#include <sstream>

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



	Label make_function_label(const ast::Function & fx) {
		std::ostringstream oss;
		oss << fx.get_resolve_namespace().to_string() 
			<< fx.get_resolve_name() 
			<< "(" 
			<< fx.parameters.simple.size()
			<< ")";
		return make_external_label(oss.str());
	}



	Label derive_skip(const Label & label) {
		return make_internal_label(label.get_name() + "_SKIP");
	}



	Label derive_except(const Label & label) {
		return make_internal_label(label.get_name() + "_EXCEPT");
	}
}