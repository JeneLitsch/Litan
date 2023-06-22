#include "object_types.hxx"
#include "print.hxx"

namespace ltn::c::trans::cxx {

	void generate_object(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent) {
		out << indent << "struct " << name << " {\n";
		print_delete_special_members(out, name, indent.in());
		out << indent.in() << name << "(" << wrapped << " value = {}) : value{std::move(value)} {};\n";
		out << indent.in() << wrapped << " value;\n";
		out << indent.in() << "bool marked = false;\n";
		out << indent.in() << "std::unique_ptr<" << name << "> next;\n";
		out << indent << "};\n";
		out << indent << "\n";
	}

	void generate_stream_object(std::ostream & out, std::string_view name, std::string_view wrapped, Indent indent) {
		out << indent << "struct " << name << " {\n";
		print_delete_special_members(out, name, indent.in());
		out << indent.in() << name << "(std::unique_ptr<" << wrapped << "> value)\n";
		out << indent.in().in() << ": data{std::move(value)}\n";
		out << indent.in().in() << ", value{std::move(data.get())} {}\n";
		out << indent.in() << name << "(" << wrapped << " * value)\n";
		out << indent.in().in() << ": value{std::move(data.get())} {}\n";
		out << indent.in() << "std::unique_ptr<" << wrapped << "> data;\n";
		out << indent.in() << wrapped << "* value;\n";
		out << indent.in() << "bool marked = false;\n";
		out << indent.in() << "std::unique_ptr<" << name << "> next;\n";
		out << indent << "};\n";
		out << indent << "\n";
	}



	void print_forward_decls(std::ostream & out, Indent indent, const std::vector<ObjectType> & objects) {
		for(const auto & obj : objects) {
			out << indent << "struct " << obj.name << ";\n"; 
		}
	}



	void print_objects(std::ostream & out, Indent indent, const std::vector<ObjectType> & objects) {
		for(const auto & obj : objects) {
			obj.print(out, obj.name, obj.data_type, indent);
		}
	}
}