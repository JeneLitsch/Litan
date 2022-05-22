#include "linking.hxx"
#include <sstream>
#include "ltna/InstructionTable.hxx"
#include <iostream>
#include "ltn/reading.hxx"
namespace ltn::a::linking {
	std::size_t toArgSize(ArgFormat argFormat) {
		switch (argFormat) {
		case ArgFormat::NONE:        return 0;
		case ArgFormat::UINT:        return 8;
		case ArgFormat::UINTx2:      return 16;
		case ArgFormat::UINT16:      return 2;
		case ArgFormat::JUMP:        return 8;
		case ArgFormat::JUMP_UINT:   return 16;
		case ArgFormat::INT:         return 8;
		case ArgFormat::FLOAT:       return 8;
		case ArgFormat::BYTE:        return 1;
		case ArgFormat::UINT_BYTExX: break;
		}
		throw std::logic_error{"Missing args size in switch-case"};
	}

	std::size_t to_inst_size(std::string_view inst) {
		const auto argFormat = instruction_table.at(inst).arg_format;
		constexpr std::size_t opcodeSize = 1;
		return opcodeSize + toArgSize(argFormat);
	} 

	AddressTable scan(std::istream & in) {
		std::uint64_t position = 0;
		AddressTable table;
		std::string line;
		while(std::getline(in >> std::ws, line)) {
			std::stringstream ss(line);
			const auto inst = read<std::string>(ss);
			if(is_jumpmark(inst)) {
				const std::string label = inst.substr(1); 
				if(table.contains(label)) {
					throw std::runtime_error("Redefinition of label " + label);
				}
				table.emplace(label, position);
			}
			else if(instruction_table.at(inst).arg_format == ArgFormat::UINT_BYTExX) {
				const auto size = read<std::uint64_t>(ss);
				position += 1 + 8 + size;
			}
			else {
				position += to_inst_size(inst);
			}
		}
		return table;
	}
}