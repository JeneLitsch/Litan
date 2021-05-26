#include "VM.hxx"
#include "Assembler.hxx"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "TextExtension.hxx"

void benchmark(const ltn::ByteCode & instructions, unsigned number){
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

ltn::ByteCode assemble(const std::string & file){
	std::cout << ">> Assembling..." << std::endl;
	ltn::Assembler asmr;
	// demo instruction for custom user extension 
	asmr.registerAlias("helloWorld", ltn::IExtension::Slot::_0, 0);
	
	ltn::Script script = ltn::Script::load(file);
	ltn::ByteCode byteCode = asmr.assemble(script);

	std::cout << ">> Finished assembling" << std::endl;

	std::size_t i = 1;
	for(std::uint64_t inst : byteCode.getInstructions()){
		std::cout << i << "    " << std::setfill('0') << std::setw(16) << std::hex << inst << std::dec << std::endl;
		i++;	
	}
	return byteCode;
}

void launch(const ltn::ByteCode & instructions){
	std::cout << ">> Creating virual machine..." << std::endl;
	ltn::VM vm;
	TextExtension ext;
	vm.installExtension(ext, ltn::IExtension::Slot::_0);
	std::cout << ">> Initialising vm" << std::endl;
	vm.init(instructions);
	vm.reset();
	std::cout << ">> Starting vm" << std::endl;
	vm.run();
	std::cout << ">> Terminated" << std::endl;
}

void until(const ltn::ByteCode & instructions){
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
