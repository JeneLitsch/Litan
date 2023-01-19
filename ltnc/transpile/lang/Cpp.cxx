#include "Cpp.hxx"

namespace ltn::c::lang {
	namespace {
		void print_type(std::ostream & oss, const type::Type & type) {
			oss << "auto";
		}


		void print_full_name(std::ostream & oss, const sst::Functional & fx) {
			for(const auto & level : fx.namespaze) {
				oss << level << "_";
			}
			oss << fx.name << "_" << fx.parameters.size();
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



	std::string Cpp::fx_start(const sst::Functional & fx) const {
		std::ostringstream oss;
		print_type(oss, fx.return_type);
		oss << " ";
		print_full_name(oss, fx);
		print_parameters(oss, fx);
		oss << "{ ";
		return oss.str();
	}



	std::string Cpp::fx_end(const sst::Functional & fx) const {
		return "}";
	}



	std::string Cpp::type_name(const type::Type & type) const {
		std::ostringstream oss;
		print_type(oss, type);
		return oss.str();
	}
};