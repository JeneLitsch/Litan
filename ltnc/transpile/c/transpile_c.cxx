#include "transpile_c.hxx"

namespace ltn::c::trans::cxx {
	namespace {
		void print_includes(std::ostream & stream) {
			stream << "#include <cstdint>\n";
			stream << "#include <concepts>\n";
			stream << "#include <iostream>\n";
			stream << "#include <vector>\n";
			stream << "\n";
		}



		void print_value_type_enum(std::ostream & stream, Indent indent) {
			stream << indent << "enum ValueType {\n";
			stream << indent.in() << "NVLL = 0x00,\n";
			stream << indent.in() << "BOOL = 0x10, INT, FLOAT, CHAR,\n";
			stream << indent.in() << "ARRAY = 0x20, STRING, TUPLE,\n";
			stream << indent.in() << "ISTREAM = 0x30, OSTREAM,\n";
			stream << indent.in() << "FX_PTR = 0x40, ITERATOR, ITERATOR_STOP,\n";
			stream << indent.in() << "CLOCK = 0x50,\n";
			stream << indent.in() << "STRUCT = 0x60,\n";
			stream << indent.in() << "QUEUE = 0x70, STACK, MAP,\n";
			stream << indent.in() << "RNG = 0x80, TYPE,\n";
			stream << indent << "};\n";
			stream << indent << "\n";
		}



		void print_value_class(std::ostream & stream, Indent indent) {
			stream << indent << "struct Value {\n";
			stream << indent.in() << "union Val {\n";
			stream << indent.in().in() << "uint8_t b;\n";
			stream << indent.in().in() << "uint8_t c;\n";
			stream << indent.in().in() << "int64_t i;\n";
			stream << indent.in().in() << "double f;\n";
			stream << indent.in() << "};\n";
			stream << indent.in() << "Value(ValueType type, Val val) : type{type}, val{val} {}\n";
			stream << indent.in() << "uint32_t type;\n";
			stream << indent.in() << "Val val;\n";
			stream << indent << "};\n\n";
		}



		void print_context_class(std::ostream & stream, Indent indent) {
			stream << indent << "struct Context {\n";
			stream << indent.in() << "void push_root(Value * value) {\n";
			stream << indent.in().in() << "roots.push_back(value);\n"; 
			stream << indent.in().in() << "std::cout << \"Push\" << roots.size() << \"\\n\";\n"; 
			stream << indent.in() << "}\n";
			stream << indent.in() << "void pop_root() {\n";
			stream << indent.in().in() << "std::cout << \"Pop\" << roots.size() << \"\\n\";\n"; 
			stream << indent.in().in() << "roots.pop_back();\n"; 
			stream << indent.in() << "}\n"; 
			stream << indent.in() << "std::vector<const Value *> roots;\n"; 
			stream << indent << "};\n\n";
		}



		void print_value_wrapper_class(std::ostream & stream, Indent indent, std::string_view name) {
			stream << indent << "class " << name << " final {\n";
			stream << indent << "public:\n";
			
			stream << indent.in() << name << "(const Value & value) : value {value} {\n";
			stream << indent.in().in() << "context.push_root(&this->value);\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << "~" << name << "() {\n";
			stream << indent.in().in() << "context.pop_root();\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << name << " & operator=(const Value & value) {\n";
			stream << indent.in().in() << "this->value = value;\n";
			stream << indent.in().in() << "return *this;\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << "const Value & get() const {\n";
			stream << indent.in().in() << "return this->value;\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << " operator const Value &() const {\n";
			stream << indent.in().in() << "return this->value;\n";
			stream << indent.in() << "}\n";

			print_delete_special_members(stream, name, indent.in());
			stream << indent << "private:\n";
			stream << indent.in() << "Value value;\n";
			stream << indent << "};\n\n";
		}


		void print_tmp_class(std::ostream & stream, Indent indent) {
			print_value_wrapper_class(stream, indent, "Tmp");
		}


		void print_var_class(std::ostream & stream, Indent indent) {
			print_value_wrapper_class(stream, indent, "Var");
		}



		void print_main(std::ostream & stream) {
			stream << "int main() {\n";
			stream << "\treturn fx::main_1(ltn::value_null()).val.i;\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_value_null(std::ostream & stream, Indent indent) {
			stream << indent << "struct Value value_null() {\n";
			stream << indent.in() << "return Value {NVLL, Value::Val {} };\n";
			stream << indent << "}\n\n";
		}


		void print_value_xyz(
			std::ostream & stream,
			Indent indent,
			std::string_view name,
			std::string_view ltn_type,
			std::string_view c_type,
			std::string_view member) {
			
			stream << indent << "struct Value value_" << name << "(" << c_type << " x) {\n";
			stream << indent.in() << "return Value {" << ltn_type << ", Value::Val { ." << member << " = x } };\n";
			stream << indent << "}\n\n";
		}



		void print_wrapped_operator(
			std::ostream & stream,
			std::string_view name,
			std::string_view op,
			Indent indent) {

			auto indent_1 = indent.in();
			
			stream << indent << "Value " << name << "_impl(std::integral auto l, std::integral auto r) {\n";
			stream << indent_1 << "auto x = static_cast<std::int64_t>(l)" << op << "static_cast<std::int64_t>(r);\n";
			stream << indent_1 << "return value_int(x);\n";
			stream << indent << "}\n\n";

			stream << indent << "Value " << name << "_impl(std::integral auto l, std::floating_point auto r) {\n";
			stream << indent_1 << "auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
			stream << indent_1 << "return value_float(x);\n";
			stream << indent << "}\n\n";

			stream << indent << "Value " << name << "_impl(std::floating_point auto l, std::integral auto r) {\n";
			stream << indent_1 << "auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
			stream << indent_1 << "return value_float(x);\n";
			stream << indent << "}\n\n";

			stream << indent << "Value " << name << "_impl(std::floating_point auto l, std::floating_point auto r) {\n";
			stream << indent_1 << "auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
			stream << indent_1 << "return value_float(x);\n";
			stream << indent << "}\n\n";
		}



		void print_arith_dispatch(std::ostream & stream, std::string_view name, Indent indent) {
			auto indent_1 = indent.in();
			auto indent_2 = indent_1.in();
			auto indent_3 = indent_2.in();
			stream << indent << "Value " << name << "(const Value & l, const Value & r){\n";
			stream << indent_1 << "switch(l.type) {\n";
			stream << indent_2 << "case BOOL: switch(r.type) {\n";
			stream << indent_3 << "case BOOL  : return " << name << "_impl(l.val.b, r.val.b);" "\n";
			stream << indent_3 << "case CHAR  : return " << name << "_impl(l.val.b, r.val.c);" "\n";
			stream << indent_3 << "case INT   : return " << name << "_impl(l.val.b, r.val.i);" "\n";
			stream << indent_3 << "case FLOAT : return " << name << "_impl(l.val.b, r.val.f);" "\n";
			stream << indent_2 << "}\n";
			stream << indent_2 << "case CHAR: switch(r.type) {\n";
			stream << indent_3 << "case BOOL  : return " << name << "_impl(l.val.c, r.val.b);" "\n";
			stream << indent_3 << "case CHAR  : return " << name << "_impl(l.val.c, r.val.c);" "\n";
			stream << indent_3 << "case INT   : return " << name << "_impl(l.val.c, r.val.i);" "\n";
			stream << indent_3 << "case FLOAT : return " << name << "_impl(l.val.c, r.val.f);" "\n";
			stream << indent_2 << "}\n";
			stream << indent_2 << "case INT: switch(r.type) {\n";
			stream << indent_3 << "case BOOL  : return " << name << "_impl(l.val.i, r.val.b);" "\n";
			stream << indent_3 << "case CHAR  : return " << name << "_impl(l.val.i, r.val.c);" "\n";
			stream << indent_3 << "case INT   : return " << name << "_impl(l.val.i, r.val.i);" "\n";
			stream << indent_3 << "case FLOAT : return " << name << "_impl(l.val.i, r.val.f);" "\n";
			stream << indent_2 << "}\n";
			stream << indent_2 << "case FLOAT: switch(r.type) {\n";
			stream << indent_3 << "case BOOL  : return " << name << "_impl(l.val.f, r.val.b);" "\n";
			stream << indent_3 << "case CHAR  : return " << name << "_impl(l.val.f, r.val.c);" "\n";
			stream << indent_3 << "case INT   : return " << name << "_impl(l.val.f, r.val.i);" "\n";
			stream << indent_3 << "case FLOAT : return " << name << "_impl(l.val.f, r.val.f);" "\n";
			stream << indent_2 << "}\n";
			stream << indent_1 << "}\n";
			stream << indent << "}\n";
			stream << "\n";
		}



		void print_unary(
			std::ostream & stream,
			std::string_view name,
			std::string_view op,
			Indent indent) {

			auto indent_1 = indent.in();
			auto indent_2 = indent_1.in();
			
			stream << indent << "Value " << name << "(const Value & x) {\n";
			stream << indent_1 << "switch(x.type) {\n";
			stream << indent_2 << "case BOOL : return value_int(-static_cast<std::int64_t>(x.val.b));\n";
			stream << indent_2 << "case CHAR : return value_int(-static_cast<std::int64_t>(x.val.c));\n";
			stream << indent_2 << "case INT  : return value_int(-static_cast<std::int64_t>(x.val.i));\n";
			stream << indent_2 << "case FLOAT: return value_float(-static_cast<double>(x.val.f));\n";
			stream << indent_1 << "}\n";
			stream << indent << "}\n";
			stream << "\n";
		}



		void print_gc(std::ostream & out, Indent indent) {
			out << indent << "void gc(const Context & cnxt) {\n";
			out << indent.in() << "for(auto * root : cnxt.roots) {\n";
			out << indent.in().in() << "std::cout << \"ROOT\\n\";\n";
			out << indent.in() << "}\n";
			out << indent << "}\n\n";
		}
	}

	std::string transpile_c(const sst::Program & program) {
		std::ostringstream oss;
		
		print_includes(oss);
		Indent indent_ns {1};

		oss << "namespace ltn {\n";

		print_value_type_enum(oss, indent_ns);
		print_value_class(oss, indent_ns);
		print_context_class(oss, indent_ns);
		oss << indent_ns << "Context context;\n\n";
		print_var_class(oss, indent_ns);
		print_tmp_class(oss, indent_ns);

		print_gc(oss, indent_ns);

		print_value_null(oss, indent_ns);
		print_value_xyz(oss, indent_ns, "bool", "BOOL", "bool", "b");
		print_value_xyz(oss, indent_ns, "char", "CHAR", "std::uint8_t", "c");
		print_value_xyz(oss, indent_ns, "int", "INT", "std::int64_t", "i");
		print_value_xyz(oss, indent_ns, "float", "FLOAT", "double", "f");

		print_wrapped_operator(oss, "add", "+", indent_ns);
		print_arith_dispatch(oss, "add", indent_ns);

		print_wrapped_operator(oss, "sub", "-", indent_ns);
		print_arith_dispatch(oss, "sub", indent_ns);

		print_wrapped_operator(oss, "mlt", "*", indent_ns);
		print_arith_dispatch(oss, "mlt", indent_ns);

		print_wrapped_operator(oss, "div", "/", indent_ns);
		print_arith_dispatch(oss, "div", indent_ns);
		
		print_unary(oss, "neg", "-", indent_ns);

		oss << "}\n";

		oss << "namespace fx {\n";
		for(const auto & fx : program.functions) {
			oss << indent_ns;
			print_function_header(*fx, oss);
			oss << ";}\n";
		}
		oss << "\n";
		for(const auto & fx : program.functions) {
			oss << transpile_c_functional(*fx, indent_ns);
		}
		oss << "}\n";
		
		print_main(oss);

		return oss.str();
	}
}