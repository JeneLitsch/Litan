#include <iostream>
#include <sstream>
#include <fstream>
#include "Ltna.hxx"
#include "linking/linking.hxx"
#include "expand/expanding.hxx"

std::vector<std::uint8_t> ltn::a::Ltna::assemble(std::istream & in) const {
	const std::string code = [&] {
		std::stringstream ss;
		ss << in.rdbuf();
		return ss.str();
	}();

	std::stringstream scanStream(code);
	const auto table = linking::scan(scanStream);
	
	std::ofstream out("example/a.txt");
	std::stringstream source(code);
	std::stringstream patched;
	linking::patch(source, patched, table);
	expand::expand(patched, out);
	out.close();
	return { 1, 2, 3 };
}
