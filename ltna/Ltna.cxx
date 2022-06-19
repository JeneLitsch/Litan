#include <iostream>
#include <sstream>
#include <fstream>
#include "Ltna.hxx"
#include "assemble.hxx"
#include "parse.hxx"
#include "scan.hxx"

namespace ltn::a {
	std::vector<std::uint8_t> to_bytecode(std::istream & in) {
		const std::string code = [&] {
			std::stringstream ss;
			ss << in.rdbuf();
			return ss.str();
		}();

		std::stringstream iss(code);
		const auto instructions = parse(iss);
		const auto jump_table = scan(instructions);
		const auto bytecode = assemble(instructions, jump_table);
		return bytecode;
	}
}