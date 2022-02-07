#include "linking.hxx"
#include "ltn/reading.hxx"
#include <sstream>
#include "ltna/InstructionTable.hxx"
namespace ltn::a::linking {
	namespace {
		std::uint64_t resolveJump(
			const std::string & label,
			const AddressTable & table) {
			if(table.contains(label)) {
				return table.at(label); 
			}
			throw std::runtime_error("Undefined reference to " + label);
		}
	}

	bool isJump(ArgFormat format) {
		return format == ArgFormat::JUMP 
			|| format == ArgFormat::JUMP_UINT;
	} 

	void patch(std::istream & in, std::ostream & out, const AddressTable & table) {
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ls(line);
			const auto inst = read<std::string>(ls);
			if(inst[0] != ':') {
				const auto argFormat = instructionTable.at(inst).argFormat;
				if(isJump(argFormat)) {
					const std::string label = read<std::string>(ls);
					const std::string rest = read<std::string>(ls);
					out << inst << " "
						<< resolveJump(label, table) << " "
						<< rest << "\n";
				}
				else {
					out << line << "\n";
				}
			}
		}
	}
}