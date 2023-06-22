#include "operators.hxx"
#include "error.hxx"

namespace ltn::c::trans::cxx {
	void print_arith_dispatch(std::ostream & out, Indent indent, std::string_view name) {
		auto indent_1 = indent.in();
		auto indent_2 = indent_1.in();
		auto indent_3 = indent_2.in();
		out << indent << "Value " << name << "(const Value & l, const Value & r){\n";
		out << indent_1 << "switch(l.type) {\n";
		out << indent_2 << "case BOOL: switch(r.type) {\n";
		out << indent_3 << "case BOOL  : return " << name << "_impl(l.val.b, r.val.b);" "\n";
		out << indent_3 << "case CHAR  : return " << name << "_impl(l.val.b, r.val.c);" "\n";
		out << indent_3 << "case INT   : return " << name << "_impl(l.val.b, r.val.i);" "\n";
		out << indent_3 << "case FLOAT : return " << name << "_impl(l.val.b, r.val.f);" "\n";
		out << indent_2 << "}\n";
		out << indent_2 << "case CHAR: switch(r.type) {\n";
		out << indent_3 << "case BOOL  : return " << name << "_impl(l.val.c, r.val.b);" "\n";
		out << indent_3 << "case CHAR  : return " << name << "_impl(l.val.c, r.val.c);" "\n";
		out << indent_3 << "case INT   : return " << name << "_impl(l.val.c, r.val.i);" "\n";
		out << indent_3 << "case FLOAT : return " << name << "_impl(l.val.c, r.val.f);" "\n";
		out << indent_2 << "}\n";
		out << indent_2 << "case INT: switch(r.type) {\n";
		out << indent_3 << "case BOOL  : return " << name << "_impl(l.val.i, r.val.b);" "\n";
		out << indent_3 << "case CHAR  : return " << name << "_impl(l.val.i, r.val.c);" "\n";
		out << indent_3 << "case INT   : return " << name << "_impl(l.val.i, r.val.i);" "\n";
		out << indent_3 << "case FLOAT : return " << name << "_impl(l.val.i, r.val.f);" "\n";
		out << indent_2 << "}\n";
		out << indent_2 << "case FLOAT: switch(r.type) {\n";
		out << indent_3 << "case BOOL  : return " << name << "_impl(l.val.f, r.val.b);" "\n";
		out << indent_3 << "case CHAR  : return " << name << "_impl(l.val.f, r.val.c);" "\n";
		out << indent_3 << "case INT   : return " << name << "_impl(l.val.f, r.val.i);" "\n";
		out << indent_3 << "case FLOAT : return " << name << "_impl(l.val.f, r.val.f);" "\n";
		out << indent_2 << "}\n";
		out << indent_1 << "}\n";
		invalid_operands(out, indent_1);
		out << indent << "}\n";
		out << "\n";
	}



	void print_wrapped_operator(std::ostream & stream, Indent indent, std::string_view name, std::string_view op) {

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
}