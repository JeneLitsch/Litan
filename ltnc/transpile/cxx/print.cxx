#include "print.hxx"

namespace ltn::c::trans::cxx {
	void print_function_header(const sst::Functional & fx, std::ostream & out) {
		out << "namespace ";
		print_namespace(fx.namespaze, out);
		out << "{";
		out << "ltn::Value " << fx.name << "_" << fx.arity() << "(";
		for(std::size_t i = 0; i < fx.arity(); i++) {
			if(i) out << ",";
			out << "ltn::Var var_" << i;
		}
		out << ")";
	}



	void print_namespace(const Namespace & n, std::ostream & out) {
		for(std::size_t i = 0; i < n.size(); i++) {
			if(i) out << "::";
			out << n[i];
			if(n[i] == "std") {
				out << "_";
			}
		}
	}


	
	void print_delete_special_members(std::ostream & out, std::string_view name, Indent indent) {
		out << indent << name << "(const " << name <<  "&) = delete;\n";
		out << indent << name << "(" << name <<  "&&) = delete;\n";
		out << indent << name << "& operator=(const " << name <<  "&) = delete;\n";
		out << indent << name << "& operator=(" << name <<  "&&) = delete;\n";
	}





	void print_switch(std::ostream & out, Indent indent, std::string_view expr, const std::map<std::string, Print> & cases) {
		out << indent << "switch(" << expr << ") {\n";
		auto case_indent = indent.in(); 
		for(const auto & [key, val] : cases) {
			out << case_indent << "case " << key << ": {\n";
			val(out, case_indent.in());
			out << case_indent << "} break;\n";
		}
		out << indent << "};\n";
	}
}