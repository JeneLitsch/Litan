#include "linking.hxx"
#include <sstream>
namespace ltn::a::linking {
	namespace {
	}

	void patch(std::istream & in, std::ostream & out, const AddressTable & table) {
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ss(line);
			std::string inst;
 			ss >> inst;
			if(inst[0] != ':') {
				std::string label;
				ss >> label;
				if(inst == "jump") {
					if(table.contains(label)) {
						out << inst << " " << table.at(label) << "\n"; 
					}
					else {
						throw std::runtime_error("Undefined reference to " + label);
					}
				}
				else {
					out << line << "\n";
				}
			}
		}
	}
}