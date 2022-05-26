#include <iostream>
#include <sstream>
#include <fstream>
#include "Ltna.hxx"
#include "assemble.hxx"
#include "parse.hxx"
#include "scan.hxx"

std::vector<std::uint8_t> ltn::a::Ltna::process(std::istream & in) const {
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
