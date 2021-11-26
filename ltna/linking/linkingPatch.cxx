#include "linking.hxx"
#include <sstream>
namespace ltn::a::linking {
	namespace {
		std::string resolveJump(
			const std::string_view inst,
			const std::string & label,
			const AddressTable & table) {
			std::stringstream ss;
			if(table.contains(label)) {
				ss << inst << " " << table.at(label); 
			}
			else {
				throw std::runtime_error("Undefined reference to " + label);
			}
			return ss.str();
		}
	}

	void patch(std::istream & in, std::ostream & out, const AddressTable & table) {
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ls(line);
			std::string inst;
 			ls >> inst;
			if(inst[0] != ':') {
				std::string label;
				ls >> label;
				if(inst == "jump" || inst == "call" || inst == "ifelse") {
					out << resolveJump(inst, label, table) << "\n";
				}
				else if(inst == "newfx") {
					out << resolveJump(inst, label, table);
					std::string placeholders;
					ls >> placeholders;
					out << " " << placeholders << "\n";
				}
				else {
					out << line << "\n";
				}
			}
		}
	}
}