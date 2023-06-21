#include "transpile_c.hxx"
#include <sstream>

namespace ltn::c::trans::cxx {
	namespace {
		std::string transpile_c_function(const sst::Function & fx, Indent indent) {
			Indent inner = indent.in();
			std::ostringstream oss;
			oss << indent;
			print_function_header(fx, oss);
			oss << "{\n";
			for(std::uint64_t i = 0; i < fx.body->nested_alloc(); ++i) {
				oss << inner << "ltn::Var var_" << i + fx.arity() << " = " << "ltn::value_null()" << ";\n"; 
			}
			transpile_c_statement(*fx.body, oss, inner);
			oss << inner << "return ltn::value_null();\n"; 
			oss << indent << "}}\n";
			oss << "\n";
			return oss.str();
		}



		std::string transpile_c_build_in_function(const sst::BuildIn & fx, Indent indent) {
			Indent inner = indent.in();
			std::ostringstream oss;
			oss << indent;
			print_function_header(fx, oss);
			oss << "{\n";
			if(fx.key == "io_print") {
				oss << inner << "std::cout << ltn::stringify(var_1.get());\n"; 
				oss << inner << "return ltn::value_null();\n"; 
			}
			if(fx.key == "io_cout") {
				oss << inner << "return ltn::value_null();\n"; 
			}
			if(fx.key == "to_string") {
				oss << inner << "auto str = ltn::stringify(var_0.get());\n"; 
				oss << inner << "return ltn::value_string(std::move(str));\n"; 
			}
			oss << inner << "return ltn::value_null();\n"; 
			oss << indent << "}}\n";
			oss << "\n";
			return oss.str();
		}
	}



	std::string transpile_c_functional(const sst::Functional & functional, Indent indent) {
		if(auto fx = as<const sst::Function>(functional)) {
			return transpile_c_function(*fx, indent);
		}
		if(auto fx = as<const sst::BuildIn>(functional)) {
			return transpile_c_build_in_function(*fx, indent);
		}
		throw std::runtime_error{"Unknown functional declaration"};
	}
}