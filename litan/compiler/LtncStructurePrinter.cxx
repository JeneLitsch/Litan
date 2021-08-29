#include "LtncStructurePrinter.hxx"
#include <sstream>

ltn::c::StructurePrinter::StructurePrinter(const Program & program)
	: program(program) {}


std::string ltn::c::StructurePrinter::toString(const std::vector<std::string> & strs) {
	std::stringstream ss;
	bool first = true;
	for(const std::string & str : strs) {
		if(!first) {
			ss << ",";
		}
		else {
			first = false;
		}
		ss << str;
	}
	return ss.str();
}


std::string ltn::c::StructurePrinter::print() const {
	std::stringstream ss;

	for(const auto & fx : this->program.functionTemplates) {
		ss << "Template Fx: ";
		ss << fx->decl->signature.ns << fx->decl->signature.name;
		ss << "<"  << toString(fx->placeholders) << ">";
		ss << "\n";
	}
	
	for(const auto & fx : this->program.functions) {
		ss << "Fx: ";
		ss << fx->signature.ns << fx->signature.name;
		ss << "\n";
	}

	for(const auto & strct : this->program.structTemplates) {
		ss << "Template Struct: ";
		ss << strct->decl->typeId.ns << strct->decl->typeId.name; 
		ss << "<"  << toString(strct->placeholders) << ">";
		ss << "\n";
	}

	for(const auto & strct : this->program.structs) {
		ss << "Struct: ";
		ss << strct->typeId.ns << strct->typeId.name;
		ss << "\n";
	}

	for(const auto & typeDef : this->program.types) {
		ss << "Type: ";
		ss << typeDef->id.ns << typeDef->id.name;
		ss << "\n";
	}

	return ss.str();
}


std::ostream & ltn::c::operator<<(std::ostream & stream, const StructurePrinter & printer) {
	stream << printer.print();
	return stream;
}