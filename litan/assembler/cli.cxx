#include <Ltna.hxx>
#include <iostream>
#include "LtnFileIO.hxx"
#include "LtnaAssemblerError.hxx"
int main(int argc, char const *argv[]) {
	std::cout << "Litan Assembler (c) Jene Litsch 2021" << std::endl;
	if(argc <= 3) {
		std::cout << "Invalid Parameter for Assembler" << std::endl;
		return 1;
	}
	std::string dst = argv[1];
	std::string src = argv[2];
	std::string format = argv[3];

	std::cout << "Src: " << src << std::endl;
	std::cout << "Dst: " << dst << std::endl;
	std::cout << "Format: " << format << std::endl;
	

	std::string assembly = ltn::readFile(src);
	ltna::Ltna ltnA;
	std::vector<std::uint64_t> byteCode;
	try {
		byteCode = ltnA.assemble(assembly);
	}
	catch (ltna::AssemblerError error) {
		std::cout << "Error while assembling: " << error.what() << std::endl;
		std::cout << std::endl;
		return -1;
	}
	if (format == "-hex") {
		std::cout << ">> Assemble to hexCode" << std::endl;
		std::string hexCode = ltn::toHex(byteCode);
		ltn::writeFile(dst, hexCode);
		std::cout << ">> Done assembling!" << std::endl;
		std::cout << std::endl;
		return 0;
	}
	if (format == "-bin") {
		std::cout << ">> Assemble to binCode" << std::endl;
		std::string binCode = ltn::toBin(byteCode);
		ltn::writeFile(dst, binCode);
		std::cout << ">> Done assembling!" << std::endl;
		std::cout << std::endl;
		return 0;
	}
	std::cout << "Invalid mode" << std::endl;
	return 1;
}