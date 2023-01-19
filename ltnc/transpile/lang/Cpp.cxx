#include "Cpp.hxx"

namespace ltn::c::lang {
	namespace {
		void print_type(std::ostream & oss, const type::Type & type) {
			oss << "auto";
		}



		void print_parameters(std::ostream & oss, const sst::Functional & fx) {
			oss << "(";
			for(std::size_t i = 0; i < fx.parameters.size(); ++i) {
				auto & param = fx.parameters[i];
				if(i) oss << ", ";
				print_type(oss, param.type);
				oss << " " << param.name;
			}
			oss << ")";
		}
	}



	std::string Cpp::fx_begin(const sst::Functional & fx) const {
		std::ostringstream oss;
		print_type(oss, fx.return_type);
		oss << " ";
		oss << fx.label.mangle();
		print_parameters(oss, fx);
		oss << "{ ";
		return oss.str();
	}



	std::string Cpp::fx_end(const sst::Functional & fx) const {
		return "}";
	}



	std::string Cpp::block_begin() const {
		return "{";
	}



	std::string Cpp::block_end() const {
		return "}";
	}



	std::string Cpp::call_start(const sst::Call & call) const {
		std::ostringstream oss;
		oss << call.label.mangle() << "(";
		return oss.str();
	}



	std::string Cpp::call_end(const sst::Call & call) const {
		return ")";
	}



	std::string Cpp::call_args_separation() const {
		return ",";
	}



	std::string Cpp::type_name(const type::Type & type) const {
		std::ostringstream oss;
		print_type(oss, type);
		return oss.str();
	}



	std::string_view Cpp::keyword_true() const {
		return "true";
	}



	std::string_view Cpp::keyword_false() const {
		return "false";

	}



	std::string_view Cpp::keyword_null() const {
		return "nullptr";
	}
};