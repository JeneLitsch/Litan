#include "transpile_c.hxx"

namespace ltn::c::trans::cxx {
	namespace {
		void print_includes(std::ostream & stream) {
			stream << "#include <cstdint>\n";
			stream << "#include <concepts>\n";
			stream << "\n";
		}



		void print_value_type_enum(std::ostream & stream) {
			stream << "enum ValueType {\n";
			stream << "\tNVLL = 0x00,\n";
			stream << "\tBOOL = 0x10, INT, FLOAT, CHAR,\n";
			stream << "\tARRAY = 0x20, STRING, TUPLE,\n";
			stream << "\tISTREAM = 0x30, OSTREAM,\n";
			stream << "\tFX_PTR = 0x40, ITERATOR, ITERATOR_STOP,\n";
			stream << "\tCLOCK = 0x50,\n";
			stream << "\tSTRUCT = 0x60,\n";
			stream << "\tQUEUE = 0x70, STACK, MAP,\n";
			stream << "\tRNG = 0x80, TYPE,\n";
			stream << "};\n";
			stream << "\n";
		}



		void print_value_struct(std::ostream & stream) {
			stream << "struct Value {\n";
			stream << "\t" << "union Val {\n";
			stream << "\t\t" << "uint8_t b;\n";
			stream << "\t\t" << "uint8_t c;\n";
			stream << "\t\t" << "int64_t i;\n";
			stream << "\t\t" << "double f;\n";
			stream << "\t" << "};\n";
			stream << "\t" << "Value(ValueType type, Val val) : type{type}, val{val} {}\n";
			stream << "\t" << "uint32_t type;\n";
			stream << "\t" << "Val val;\n";
			stream << "};\n\n";
		}



		void print_main(std::ostream & stream) {
			stream << "int main() {\n";
			stream << "\treturn fx::main_1(ltn::value_null()).val.i;\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_value_null(std::ostream & stream) {
			stream << "struct Value value_null() {\n";
			stream << "\t" << "return Value {NVLL, Value::Val {} };\n";
			stream << "}\n\n";
		}


		void print_value_xyz(
			std::ostream & stream,
			std::string_view name,
			std::string_view ltn_type,
			std::string_view c_type,
			std::string_view member) {
			
			stream << "struct Value value_" << name << "(" << c_type << " x) {\n";
			stream << "\t" << "return Value {" << ltn_type << ", Value::Val { ." << member << " = x } };\n";
			stream << "}\n\n";
		}



		std::string print_arith_calc(
			std::string_view type_ret,
			std::string_view op,
			std::string_view member_l,
			std::string_view member_r) {
			std::ostringstream oss;
			oss << "return push(value_" << type_ret << "(";
			oss << "l.val." << member_l << op << "r.val." << member_r;
			oss << "));\n";
			return oss.str();
		}


		void print_wrapped_operator(
			std::ostream & stream,
			std::string_view name,
			std::string_view op) {

			stream << "Value " << name << "_impl(std::integral auto l, std::integral auto r) {\n";
			stream << "\t auto x = static_cast<std::int64_t>(l)" << op << "static_cast<std::int64_t>(r);\n";
			stream << "\t return value_int(x);\n";
			stream << "}\n\n";

			stream << "Value " << name << "_impl(std::integral auto l, std::floating_point auto r) {\n";
			stream << "\t auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
			stream << "\t return value_float(x);\n";
			stream << "}\n\n";

			stream << "Value " << name << "_impl(std::floating_point auto l, std::integral auto r) {\n";
			stream << "\t auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
			stream << "\t return value_float(x);\n";
			stream << "}\n\n";

			stream << "Value " << name << "_impl(std::floating_point auto l, std::floating_point auto r) {\n";
			stream << "\t auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
			stream << "\t return value_float(x);\n";
			stream << "}\n\n";
		}



		void print_arith_dispatch(std::ostream & stream, std::string_view name) {
			
			stream << "Value " << name << "(const Value & l, const Value & r){\n";
			stream << "\t" << "switch(l.type) {\n";
			stream << "\t\t" << "case BOOL: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL  : return " << name << "_impl(l.val.b, r.val.b);" "\n";
			stream << "\t\t\t" << "case CHAR  : return " << name << "_impl(l.val.b, r.val.c);" "\n";
			stream << "\t\t\t" << "case INT   : return " << name << "_impl(l.val.b, r.val.i);" "\n";
			stream << "\t\t\t" << "case FLOAT : return " << name << "_impl(l.val.b, r.val.f);" "\n";
			stream << "\t\t" << "}\n";
			stream << "\t\t" << "case CHAR: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL  : return " << name << "_impl(l.val.c, r.val.b);" "\n";
			stream << "\t\t\t" << "case CHAR  : return " << name << "_impl(l.val.c, r.val.c);" "\n";
			stream << "\t\t\t" << "case INT   : return " << name << "_impl(l.val.c, r.val.i);" "\n";
			stream << "\t\t\t" << "case FLOAT : return " << name << "_impl(l.val.c, r.val.f);" "\n";
			stream << "\t\t" << "}\n";
			stream << "\t\t" << "case INT: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL  : return " << name << "_impl(l.val.i, r.val.b);" "\n";
			stream << "\t\t\t" << "case CHAR  : return " << name << "_impl(l.val.i, r.val.c);" "\n";
			stream << "\t\t\t" << "case INT   : return " << name << "_impl(l.val.i, r.val.i);" "\n";
			stream << "\t\t\t" << "case FLOAT : return " << name << "_impl(l.val.i, r.val.f);" "\n";
			stream << "\t\t" << "}\n";
			stream << "\t\t" << "case FLOAT: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL  : return " << name << "_impl(l.val.f, r.val.b);" "\n";
			stream << "\t\t\t" << "case CHAR  : return " << name << "_impl(l.val.f, r.val.c);" "\n";
			stream << "\t\t\t" << "case INT   : return " << name << "_impl(l.val.f, r.val.i);" "\n";
			stream << "\t\t\t" << "case FLOAT : return " << name << "_impl(l.val.f, r.val.f);" "\n";
			stream << "\t\t" << "}\n";
			stream << "\t" << "}\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_unary(
			std::ostream & stream,
			std::string_view name,
			std::string_view op) {
			
			stream << "Value " << name << "(const Value & x) {\n";
			stream << "\t" << "switch(x.type) {\n";
			stream << "\t\t" << "case BOOL : return value_int(-static_cast<std::int64_t>(x.val.b));\n";
			stream << "\t\t" << "case CHAR : return value_int(-static_cast<std::int64_t>(x.val.c));\n";
			stream << "\t\t" << "case INT  : return value_int(-static_cast<std::int64_t>(x.val.i));\n";
			stream << "\t\t" << "case FLOAT: return value_float(-static_cast<double>(x.val.f));\n";
			stream << "\t" << "}\n";
			stream << "}\n";
			stream << "\n";
		}
	}

	std::string transpile_c(const sst::Program & program) {
		std::ostringstream oss;
		
		print_includes(oss);

		oss << "namespace ltn {\n";

		print_value_type_enum(oss);
		print_value_struct(oss);
		print_value_null(oss);
		print_value_xyz(oss, "bool", "BOOL", "bool", "b");
		print_value_xyz(oss, "char", "CHAR", "std::uint8_t", "c");
		print_value_xyz(oss, "int", "INT", "std::int64_t", "i");
		print_value_xyz(oss, "float", "FLOAT", "double", "f");

		print_wrapped_operator(oss, "add", "+");
		print_arith_dispatch(oss, "add");

		print_wrapped_operator(oss, "sub", "-");
		print_arith_dispatch(oss, "sub");

		print_wrapped_operator(oss, "mlt", "*");
		print_arith_dispatch(oss, "mlt");

		print_wrapped_operator(oss, "div", "/");
		print_arith_dispatch(oss, "div");
		
		print_unary(oss, "neg", "-");

		oss << "}\n";

		oss << "namespace fx {\n";
		Indent indent {1};
		for(const auto & fx : program.functions) {
			oss << indent;
			print_function_header(*fx, oss);
			oss << ";\n";
		}
		oss << "\n";
		for(const auto & fx : program.functions) {
			oss << transpile_c_functional(*fx, indent);
		}
		oss << "}\n";
		
		print_main(oss);

		return oss.str();
	}
}