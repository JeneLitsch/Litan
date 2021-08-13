#include "LtncStructurePrinter.hxx"
#include <sstream>

ltn::c::StructurePrinter::StructurePrinter(const Program & program)
	: program(program) {}

std::string ltn::c::StructurePrinter::print() const {
	std::stringstream ss;
	for(const auto & fx : this->program.functions) {
		ss << "Fx: ";
		ss << fx->signature.ns << fx->signature.name;
		ss << "\n";
	}

	for(const auto & strct : this->program.structs) {
		ss << "struct: ";
		ss << strct->typeId.ns << strct->typeId.name;
		ss << "\n";
	}

	for(const auto & typeDef : this->program.types) {
		ss << "type: ";
		ss << typeDef->id.ns << typeDef->id.name;
		ss << "\n";
	}

	return ss.str();
}


std::ostream & ltn::c::operator<<(std::ostream & stream, const StructurePrinter & printer) {
	stream << printer.print();
	return stream;
}