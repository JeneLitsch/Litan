#include "ltna/Ltna.hxx"
#include "Args.hxx"
#include <fstream>
int main(int argc, char const *argv[]) {
	const ltn::a::Args args{argv, static_cast<std::size_t>(argc)};
	std::ifstream ifile(args.getSource());
	std::ofstream ofile(args.getTarget(), std::ios::binary);
	ltn::a::Ltna ltna;
	auto bytecode = ltna.assemble(ifile);
	for(auto byte : bytecode) {
		ofile << byte;
	}

	return 0;
}

