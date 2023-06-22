#include "operators.hxx"
#include "error.hxx"
#include "utils.hxx"
#include "print.hxx"

namespace ltn::c::trans::cxx {
	void binary_dispatch(std::ostream & out, Indent indent, std::string_view name,
		const std::vector<std::array<std::string, 4>> & operands) {
		
		out << indent << "Value " << name << "(const Value & l, const Value & r){\n";
		out << indent.in() << "switch(combine(l.type, r.type)) {\n";

		for(auto & [l, r, l_member, r_member] : operands) {
			out << indent.in().in() 
				<< "case combine(VT::" << l << ", VT::" << r << ") : return "
				<< name << "_impl("
				<< "l.val." << l_member << ", r.val." << r_member 
				<< ");\n";
		}

		out << indent.in() << "}\n";
		invalid_operands(out, indent.in());
		out << indent << "}\n";
		out << "\n";
	}


	void arith_dispatch(std::ostream & out, Indent indent, std::string_view name) {
		return binary_dispatch(out, indent, name, {
			{"BOOL", "BOOL",  "b", "b"},
			{"BOOL", "CHAR",  "b", "c"},
			{"BOOL", "INT",   "b", "i"},
			{"BOOL", "FLOAT", "b", "f"},

			{"CHAR", "BOOL",  "c", "b"},
			{"CHAR", "CHAR",  "c", "c"},
			{"CHAR", "INT",   "c", "i"},
			{"CHAR", "FLOAT", "c", "f"},

			{"INT", "BOOL",   "i", "b"},
			{"INT", "CHAR",   "i", "c"},
			{"INT", "INT",    "i", "i"},
			{"INT", "FLOAT",  "i", "f"},

			{"FLOAT", "BOOL",  "f", "b"},
			{"FLOAT", "CHAR",  "f", "c"},
			{"FLOAT", "INT",   "f", "i"},
			{"FLOAT", "FLOAT", "f", "f"},
		});
	}



	void add_dispatch(std::ostream & out, Indent indent) {
		return binary_dispatch(out, indent, "add", {
			{"BOOL", "BOOL",  "b", "b"},
			{"BOOL", "CHAR",  "b", "c"},
			{"BOOL", "INT",   "b", "i"},
			{"BOOL", "FLOAT", "b", "f"},

			{"CHAR", "BOOL",  "c", "b"},
			{"CHAR", "CHAR",  "c", "c"},
			{"CHAR", "INT",   "c", "i"},
			{"CHAR", "FLOAT", "c", "f"},

			{"INT", "BOOL",   "i", "b"},
			{"INT", "CHAR",   "i", "c"},
			{"INT", "INT",    "i", "i"},
			{"INT", "FLOAT",  "i", "f"},

			{"FLOAT", "BOOL",  "f", "b"},
			{"FLOAT", "CHAR",  "f", "c"},
			{"FLOAT", "INT",   "f", "i"},
			{"FLOAT", "FLOAT", "f", "f"},

			{"ARRAY", "ARRAY", "arr", "arr"},
			{"STRING", "STRING", "str", "str"},
			{"TUPLE", "TUPLE", "tup", "tup"},
		});
	}
	


	void wrap_binary_operator(std::ostream & stream, Indent indent, std::string_view name, std::string_view op) {
		stream << indent << "Value " << name << "_impl(std::integral auto l, std::integral auto r) {\n";
		stream << indent.in() << "auto x = static_cast<std::int64_t>(l)" << op << "static_cast<std::int64_t>(r);\n";
		stream << indent.in() << "return value_int(x);\n";
		stream << indent << "}\n\n";

		stream << indent << "Value " << name << "_impl(std::integral auto l, std::floating_point auto r) {\n";
		stream << indent.in() << "auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
		stream << indent.in() << "return value_float(x);\n";
		stream << indent << "}\n\n";

		stream << indent << "Value " << name << "_impl(std::floating_point auto l, std::integral auto r) {\n";
		stream << indent.in() << "auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
		stream << indent.in() << "return value_float(x);\n";
		stream << indent << "}\n\n";

		stream << indent << "Value " << name << "_impl(std::floating_point auto l, std::floating_point auto r) {\n";
		stream << indent.in() << "auto x = static_cast<double>(l)" << op << "static_cast<double>(r);\n";
		stream << indent.in() << "return value_float(x);\n";
		stream << indent << "}\n\n";
	}



	void print_concat(std::ostream & out, Indent indent) {
		out << indent << "Value add_impl(const String * l, const String * r) {\n";
		out << indent.in() << "return value_string(l->value + r->value);\n";
		out << indent << "}\n\n";

		out << indent << "Value add_impl(const Array * l, const Array * r) {\n";
		out << indent.in() << "auto x = l->value;\n";
		out << indent.in() << "for(const auto & elem : r->value) x.push_back(elem);\n";
		out << indent.in() << "return value_array(std::move(x));\n";
		out << indent << "}\n\n";

		out << indent << "Value add_impl(const Tuple * l, const Tuple * r) {\n";
		out << indent.in() << "auto x = l->value;\n";
		out << indent.in() << "for(const auto & elem : r->value) x.push_back(elem);\n";
		out << indent.in() << "return value_tuple(std::move(x));\n";
		out << indent << "}\n\n";
	}



	void unary_dispatch(
		std::ostream & stream,
		std::string_view name,
		Indent indent) {

		stream << indent << "Value " << name << "(const Value & x) {\n";
		print_switch(stream, indent.in(), "x.type", {
			{"Value::Type::BOOL", [&] (std::ostream & out, Indent indent) {
				out << indent << "return " << name << "_impl(x.val.b);\n";
			}},
			{"Value::Type::CHAR", [&] (std::ostream & out, Indent indent) {
				out << indent << "return " << name << "_impl(x.val.c);\n";
			}},
			{"Value::Type::INT", [&] (std::ostream & out, Indent indent) {
				out << indent << "return " << name << "_impl(x.val.i);\n";
			}},
			{"Value::Type::FLOAT", [&] (std::ostream & out, Indent indent) {
				out << indent << "return " << name << "_impl(x.val.f);\n";
			}},
		});

		invalid_operands(stream, indent.in());

		stream << indent << "}\n";
		stream << "\n";
	}


	void wrap_unary_operator(std::ostream & stream, Indent indent, std::string_view name, std::string_view op) {
		stream << indent << "Value " << name << "_impl(std::integral auto x) {\n";
		stream << indent.in() << "return value_int(" << op <<  "static_cast<std::int64_t>(x));\n";
		stream << indent << "}\n\n";

		stream << indent << "Value " << name << "_impl(std::floating_point auto x) {\n";
		stream << indent.in() << "return value_float(" << op <<  "static_cast<double>(x));\n";
		stream << indent << "}\n\n";
	}
}