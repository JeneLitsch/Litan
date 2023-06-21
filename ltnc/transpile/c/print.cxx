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



	void print_object_wrapper(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent) {
		out << indent << "struct " << name << " {\n";
		out << indent.in() << wrapped << " value;\n";
		out << indent.in() << "bool marked = false;\n";
		out << indent.in() << "std::unique_ptr<" << name << "> next;\n";
		out << indent << "};\n";
		out << indent << "\n";
	}



	void print_sweep(std::ostream & out, Indent indent) {
		out << indent << "template<typename Obj>\n";
		out << indent << "void sweep(std::unique_ptr<Obj> * obj) {\n";
		out << indent.in() << "while(*obj) {\n";
		out << indent.in().in() << "if(!(*obj)->marked) {\n";
		out << indent.in().in().in() << "std::cout << \"FREE\";\n";
		out << indent.in().in().in() << "*obj = std::move((*obj)->next);\n";
		out << indent.in().in() << "}\n";
		out << indent.in().in() << "else{\n";
		out << indent.in().in().in() << "(*obj)->marked = false;\n";
		out << indent.in().in().in() << "obj = &(*obj)->next;\n";
		out << indent.in().in() << "}\n";
		out << indent.in() << "};\n";
		out << indent << "};\n";
		out << indent << "\n";
	}
}