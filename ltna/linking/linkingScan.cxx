#include "linking.hxx"
#include <sstream>
namespace ltn::a::linking {
	namespace {
		using SizeTable = std::unordered_map<std::string_view, std::uint64_t>; 
		std::uint64_t getInstSize(std::string_view inst) {
			const static SizeTable sizeTable {
				{"newu", 9},
				{"newi", 9},
				{"newf", 9},
				{"goto", 9},
				{"call", 9},
			};
			if(sizeTable.contains(inst)) {
				return sizeTable.at(inst);
			}
			return 1;
		}
	}

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
				position += getInstSize(inst);
			}
			;
		}
		return table;
	}
}