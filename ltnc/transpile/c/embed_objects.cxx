#include "embed_objects.hxx"
#include "print.hxx"

namespace ltn::c::trans::cxx {

	void embed_object(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent) {
		out << indent << "struct " << name << " {\n";
		print_delete_special_members(out, name, indent.in());
		out << indent.in() << name << "(" << wrapped << " value = {}) : value{std::move(value)} {};\n";
		out << indent.in() << wrapped << " value;\n";
		out << indent.in() << "bool marked = false;\n";
		out << indent.in() << "std::unique_ptr<" << name << "> next;\n";
		out << indent << "};\n";
		out << indent << "\n";
	}

}