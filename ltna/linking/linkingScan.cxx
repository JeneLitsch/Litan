#include "linking.hxx"
#include <sstream>
#include "ltna/InstructionTable.hxx"
#include <iostream>
namespace ltn::a::linking {
	AddressTable scan(std::istream & in) {
		std::uint64_t position = 0;
		AddressTable table;
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ss(line);
			std::string inst;
 			ss >> inst;
			if(inst[0] == ':') {
				const std::string label = inst.substr(1); 
				if(table.contains(label)) {
					throw std::runtime_error("Redefinition of label " + label);
				}
				table.emplace(label, position);
			}
			else {
				const auto [opcode, size, args] = instructionTable.at(inst);
				position += size;
			}
		}
		return table;
	}
}