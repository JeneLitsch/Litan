#include "ltna/Ltna.hxx"
#include "Args.hxx"
#include "ltn/version.hxx"
#include <fstream>
int main(int argc, char const *argv[]) {
	if(argc > 1) {
		if(ltn::print_version(argv[1])) {
			return 0;
		}
	}
	const ltn::a::Args args{argv, static_cast<std::size_t>(argc)};
	std::ifstream ifile(args.get_source());
	std::ofstream ofile(args.get_target(), std::ios::binary);
	auto bytecode = ltn::a::to_bytecode(ifile);
	for(auto byte : bytecode) {
		ofile << byte;
	}

	return 0;
}

