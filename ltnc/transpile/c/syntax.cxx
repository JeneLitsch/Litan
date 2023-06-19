#include "syntax.hxx"

namespace ltn::c::trans::c {
	void print_indent(std::ostream & stream, std::uint64_t indent) {
		for(std::uint64_t i = 0; i < indent; ++i) {
			stream << '\t';
		}
	}
	
	

	void print_c(std::ostream & stream, const Variable & variable, std::uint64_t indent) {
		print_indent(stream, indent);
		stream << variable.type << " " << variable.name << " = " << variable.value << ";\n";
	}



	void print_c(std::ostream & stream, const Member & variable, std::uint64_t indent) {
		print_indent(stream, indent);
		stream << variable.type << " " << variable.name << ";\n";
	}



	void print_c(std::ostream & stream, const Struct & strukt, std::uint64_t indent) {
		print_indent(stream, indent);
		stream << "struct " << strukt.name << "{\n";
		for(const auto & member : strukt.members) {
			print_c(stream, member, indent+1);
		}
		print_indent(stream, indent);
		stream << "};\n";
	}



	void print_c(std::ostream & stream, const Function & fx, std::uint64_t indent) {
		stream << "void " << fx.name << "_" << fx.arity << "()";
		fx.body.print(stream, indent);
	}



	void print_c(std::ostream & stream, const Block & block, std::uint64_t indent) {
		stream << "{\n";
		for(const auto & elem : block.elements) {
			elem.print(stream, indent + 1);
		}
		print_indent(stream, indent);
		stream << "}";
	}



	void print_c(std::ostream & stream, const Line & line, std::uint64_t indent) {
		print_indent(stream, indent);
		stream << line.code << "\n";
	}



	void print_c(std::ostream & stream, const Include & include, std::uint64_t indent) {
		stream << "#include " << include.header << "\n";
	}



	void print_c(std::ostream & stream, const Bundle & file, std::uint64_t indent) {
		for(const auto & elem : file.elements) {
			elem.print(stream, indent);
		}
	}
}