#include "primitive_types.hxx"
#include "utils.hxx"

namespace ltn::c::trans::cxx {
	void generate_value_null(const PrimitiveType &, std::ostream & stream, Indent indent) {
		stream << indent << "struct Value value_null() {\n";
		stream << indent.in() << "return Value {NVLL, Value::Val {} };\n";
		stream << indent << "}\n\n";
	}



	void generate_value_primitive(const PrimitiveType & type, std::ostream & stream, Indent indent) {
		stream << indent << "struct Value value_" << type.name << "(" << type.data_type << " x) {\n";
		stream << indent.in() << "return Value {" << to_uppercase(type.name) << ", Value::Val { ." << type.value_member << " = x } };\n";
		stream << indent << "}\n\n";
	}
}