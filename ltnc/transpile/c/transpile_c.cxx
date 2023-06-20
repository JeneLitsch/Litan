#include "transpile_c.hxx"

namespace ltn::c::trans::cxx {
	namespace {
		void print_includes(std::ostream & stream) {
			stream << "#include <stdint.h>\n";
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
			stream << "\t" << "uint32_t type;\n";
			stream << "\t" << "union {\n";
			stream << "\t\t" << "uint8_t b;\n";
			stream << "\t\t" << "uint8_t c;\n";
			stream << "\t\t" << "int64_t i;\n";
			stream << "\t\t" << "double f;\n";
			stream << "\t" << "} val;\n";
			stream << "};\n\n";
		}



		void print_push(std::ostream & stream) {
			stream << "void push(struct Value value) {\n";
			stream << "\t*(stack_ptr++) = value;\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_pop(std::ostream & stream) {
			stream << "struct Value pop() {\n";
			stream << "\treturn *(--stack_ptr);\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_stack(std::ostream & stream) {
			stream << "struct Value stack[1024];\n";
			stream << "struct Value * stack_ptr = 0;\n";
			stream << "struct Value * base_ptr = 0;\n";
			stream << "\n";
		}



		void print_main(std::ostream & stream) {
			stream << "int main() {\n";
			stream << "\tstack_ptr = stack;\n";
			stream << "\tbase_ptr = stack;\n";
			stream << "\tfx_main_0();\n";
			stream << "\tprintf(\"%f\\n\", pop().val.f);\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_value_null(std::ostream & stream) {
			stream << "struct Value value_null() {\n";
			stream << "\t" << "struct Value value;\n";
			stream << "\t" << "value.type = NVLL;\n";
			stream << "\t" << "return value;\n";
			stream << "}\n\n";
		}


		void print_value_xyz(
			std::ostream & stream,
			std::string_view name,
			std::string_view ltn_type,
			std::string_view c_type,
			std::string_view member) {
			
			stream << "struct Value value_" << name << "(" << c_type << " x) {\n";
			stream << "\t" << "struct Value value;\n";
			stream << "\t" << "value.type = " << ltn_type << ";\n";
			stream << "\t" << "value.val." << member << " = x;\n";
			stream << "\t" << "return value;\n";
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



		void print_arith(
			std::ostream & stream,
			std::string_view name,
			std::string_view op) {
			
			stream << "void op_" << name << "(){\n";
			stream << "\t" << "struct Value r = pop();\n";
			stream << "\t" << "struct Value l = pop();\n";

			stream << "\t" << "switch(l.type) {\n";
			stream << "\t\t" << "case BOOL: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL  :" << print_arith_calc("int",   op, "b", "b");
			stream << "\t\t\t" << "case CHAR  :" << print_arith_calc("int",   op, "b", "c");
			stream << "\t\t\t" << "case INT   :" << print_arith_calc("int",   op, "b", "i");
			stream << "\t\t\t" << "case FLOAT :" << print_arith_calc("float", op, "b", "f");
			stream << "\t\t" << "}\n";
			stream << "\t\t" << "case CHAR: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL  :" << print_arith_calc("int",   op, "c", "b");
			stream << "\t\t\t" << "case CHAR  :" << print_arith_calc("int",   op, "c", "c");
			stream << "\t\t\t" << "case INT   :" << print_arith_calc("int",   op, "c", "i");
			stream << "\t\t\t" << "case FLOAT :" << print_arith_calc("float", op, "c", "f");
			stream << "\t\t" << "}\n";
			stream << "\t\t" << "case INT: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL :" << print_arith_calc("int",   op, "i", "b");
			stream << "\t\t\t" << "case CHAR :" << print_arith_calc("int",   op, "i", "c");
			stream << "\t\t\t" << "case INT  :" << print_arith_calc("int",   op, "i", "i");
			stream << "\t\t\t" << "case FLOAT:" << print_arith_calc("float", op, "i", "f");
			stream << "\t\t" << "}\n";
			stream << "\t\t" << "case FLOAT: switch(r.type) {\n";
			stream << "\t\t\t" << "case BOOL :" << print_arith_calc("float", op, "f", "b");
			stream << "\t\t\t" << "case CHAR :" << print_arith_calc("float", op, "f", "c");
			stream << "\t\t\t" << "case INT  :" << print_arith_calc("float", op, "f", "i");
			stream << "\t\t\t" << "case FLOAT:" << print_arith_calc("float", op, "f", "f");
			stream << "\t\t" << "}\n";
			stream << "\t" << "}\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_unary(
			std::ostream & stream,
			std::string_view name,
			std::string_view op) {
			
			stream << "void op_" << name << "() {\n";
			stream << "\t" << "struct Value x = pop();\n";
			stream << "\t" << "switch(x.type) {\n";
			stream << "\t\t" << "case BOOL : return push(value_int(" << op << "x.val.b));\n";
			stream << "\t\t" << "case CHAR : return push(value_int(" << op << "x.val.c));\n";
			stream << "\t\t" << "case INT  : return push(value_int(" << op << "x.val.i));\n";
			stream << "\t\t" << "case FLOAT: return push(value_float(" << op << "x.val.f));\n";
			stream << "\t" << "}";
			stream << "}\n";
			stream << "\n";
		}
	}

	std::string transpile_c(const sst::Program & program) {
		std::ostringstream oss;
		print_includes(oss);
		print_value_type_enum(oss);
		print_value_struct(oss);
		print_stack(oss);
		print_push(oss);
		print_pop(oss);
		print_value_null(oss);

		print_value_xyz(oss, "bool", "BOOL", "uint8_t", "b");
		print_value_xyz(oss, "char", "CHAR", "uint8_t", "c");
		print_value_xyz(oss, "int", "INT", "int64_t", "i");
		print_value_xyz(oss, "float", "FLOAT", "double", "f");

		print_arith(oss, "add", "+");
		print_arith(oss, "sub", "-");
		print_arith(oss, "mlt", "*");
		print_arith(oss, "div", "/");
		
		print_unary(oss, "neg", "-");

		for(const auto & fx : program.functions) {
			oss << transpile_c_functional(*fx);
		}
		
		print_main(oss);

		return oss.str();
	}
}