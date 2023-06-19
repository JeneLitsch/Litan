#include "transpile_c.hxx"
#include <sstream>

namespace ltn::c::trans::c {
	namespace {
		std::string transpile_c_function(const sst::Function & fx) {
			Indent indent {0};
			Indent inner = indent.in();
			std::ostringstream oss;
			oss << "void fx_" << fx.name << "_" << fx.arity() << "() {\n";
			oss << inner << "struct Value * prev_base_ptr = base_ptr;\n";
			transpile_c_statement(*fx.body, oss, inner);
			oss << "}\n";
			oss << "\n";
			return oss.str();
		}



		std::string transpile_c_build_in_function(const sst::BuildIn & fx) {
			return "";
		}
	}



	std::string transpile_c_functional(const sst::Functional & functional) {
		if(auto fx = as<const sst::Function>(functional)) {
			return transpile_c_function(*fx);
		}
		if(auto fx = as<const sst::BuildIn>(functional)) {
			return transpile_c_build_in_function(*fx);
		}
		throw std::runtime_error{"Unknown functional declaration"};
	}
}