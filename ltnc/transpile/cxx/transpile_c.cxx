#include "transpile_c.hxx"
#include "embed_runtime.hxx"

namespace ltn::c::trans::cxx {
	namespace {
		void print_includes(std::ostream & stream) {
			stream << "#include <cstdint>\n";
			stream << "#include <concepts>\n";
			stream << "#include <iostream>\n";
			stream << "#include <sstream>\n";
			stream << "#include <vector>\n";
			stream << "#include <memory>\n";
			stream << "\n";
		}



		void print_main(std::ostream & stream) {
			stream << "int main() {\n";
			stream << "\tstd::cout << ltn::stringify(fx::main_1(ltn::value_null()));\n";
			stream << "}\n";
			stream << "\n";
		}
	}
	
	
	
	void transpile_globals(const sst::Program & program, std::ostream & out, Indent indent) {
		out << "namespace global {\n";
		std::size_t global_counter = 0;
		for(const auto & g : program.definitions) {
			out << indent << "ltn::Global var_" << global_counter++ << " = ";
			transpile_c_expression(*g->expr, out, indent);
			out << ";\n";
		}

		for(const auto & g : program.globals) {
			out << indent << "ltn::Global var_" << global_counter++ << " = ";
			transpile_c_expression(*g->expr, out, indent);
			out << ";\n";
		}
		out << "}\n";
	}



	void transpile_functions(const sst::Program & program, std::ostream & out, Indent indent) {
		out << "namespace fx {\n";
		for(const auto & fx : program.functions) {
			out << indent;
			print_function_header(*fx, out);
			out << ";}\n";
		}
		out << "\n";
		for(const auto & fx : program.functions) {
			out << transpile_c_functional(*fx, indent);
		}
		out << "}\n";
	}


	std::string transpile_c(const sst::Program & program) {
		std::ostringstream oss;
		
		print_includes(oss);
		Indent indent_ns {1};


		embed_runtime(oss, indent_ns);
		transpile_globals(program, oss, indent_ns);
		transpile_functions(program, oss, indent_ns);
		
		print_main(oss);

		return oss.str();
	}
}