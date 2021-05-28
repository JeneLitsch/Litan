#include "LtnFileIO.hxx"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
std::string ltn::readFile(const std::string filename) {
	std::ifstream file(filename);
	std::string content((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
	file.close();
	return content;
}

void ltn::writeFile(const std::string & filename, const std::string content) {
	std::ofstream out(filename);
	out << content;
	out.close();
}

std::string ltn::toHex(const std::vector<std::uint64_t> byteCode) {
	std::stringstream strStream;
	for(std::uint64_t instruction : byteCode) {
		strStream << std::setfill('0') << std::setw(16) << std::hex << instruction;
	}
	return strStream.str();
}

std::vector<std::uint64_t> ltn::fromHex(const std::string & hexCode) {
	if(hexCode.size() % 16 != 0){
		throw std::runtime_error("Invalid hexCode lenght");
	}
	std::size_t len = hexCode.size()/16U;
	std::vector<std::uint64_t> bytecode;
	for(int idx = 0; idx < len; idx++) {
		bytecode.push_back(std::stoull(hexCode.substr(idx * 16, 16), nullptr, 16));
	}
	return bytecode;
}

std::string ltn::toBin(const std::vector<std::uint64_t> byteCode) {
	std::stringstream strStream;
	for(std::uint64_t instruction : byteCode) {
		for(int idx = 0; idx < 8; idx++) {
			strStream << char(std::uint64_t(instruction >> 8 * (7-idx)) & 0xff); 
		}
	}
	return strStream.str();
}

std::vector<std::uint64_t> ltn::fromBin(const std::string & binCode) {
	std::size_t len = binCode.size()/8U;
	std::vector<std::uint64_t> bytecode;
	for(int idx = 0; idx < len; idx++) {
		std::uint64_t instruction = 0;
		for(int byteIdx = 0; byteIdx < 8; byteIdx++) {
			instruction |= (std::uint64_t(std::uint8_t(binCode[idx * 8 + (7-byteIdx)])) << byteIdx * 8);
		}
		// std::cout << std::setfill('0') << std::setw(16) << std::hex << instruction << std::dec << std::endl;
		bytecode.push_back(instruction);
	}
	return bytecode;
}
