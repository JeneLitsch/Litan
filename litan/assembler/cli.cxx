#include "VM.hxx"
#include "Assembler.hxx"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "Ltna.hxx"
#include "LtnFileIO.hxx"

void benchmark(const std::vector<std::uint64_t> & instructions, unsigned number){
	std::cout << ">> Creating virual machine..." << std::endl;
	ltn::VM vm;
	std::cout << ">> Initialising vm" << std::endl;
	vm.init(instructions);
	std::cout << ">> Benchmarking 100x" << std::endl;
	auto t0 = std::chrono::high_resolution_clock::now();
	for(unsigned i = 0; i < number; i++){
		vm.run();
	}
	auto t1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> delta = t1 - t0;
	std::cout << ">> Result: " << delta.count() << "ms" << std::endl;
}

std::vector<std::uint64_t> assemble(const std::string & file){
	std::cout << ">> Assembling..." << std::endl;
	ltna::Ltna ltna;
	std::vector<std::uint64_t> bytecode = ltna.assemble(ltn::readFile(file));
	std::cout << ">> Finished assembling" << std::endl;
	return bytecode;
}

void launch(const std::vector<std::uint64_t> & instructions){

	std::cout << ">> Creating virual machine..." << std::endl;
	ltn::VM vm;
	std::cout << ">> Initialising vm" << std::endl;
	vm.init(instructions);
	vm.reset();
	std::cout << ">> Starting vm" << std::endl;
	vm.run();
	std::cout << ">> Terminated" << std::endl;
}

void until(const std::vector<std::uint64_t> & instructions){
	std::cout << ">> Creating virual machine..." << std::endl;
	ltn::VM vm;
	std::cout << ">> Initialising vm" << std::endl;
	vm.init(instructions);
	std::cout << ">> Starting vm" << std::endl;
	while(true){
		switch (vm.run()) {
		case ltn::VM::Status::EXITED:
			std::cout << ">> Terminated" << std::endl;
			return;
		case ltn::VM::Status::ERROR:
			std::cout << ">> Error" << std::endl;
			return;
		case ltn::VM::Status::SUSPENDED:
			std::cout << ">> Suspended" << std::endl;
			break;
		}
	}
}

int main(int argc, char const *argv[]) {
	if(argc <= 2) return 1;
	

	if(std::string(argv[1]) == std::string("-asm")){
		launch(assemble(argv[2]));
	}

	if(std::string(argv[1]) == std::string("-until")){
		until(assemble(argv[2]));
	}

	if(std::string(argv[1]) == std::string("-bench")){
		unsigned number;
		if(argc > 3) {
			number = static_cast<unsigned>(std::stoul(argv[3]));
		}
		else{
			number = 1000;
		}

		benchmark(assemble(argv[2]),number);
	}

	return 0;
}