#include "LtnVM.hxx"
#include <iostream>
#include "LtnIoFormat.hxx"

// print or put value into ouput
void ltn::VM::print(){
	OuputFormat ouputFormat = static_cast<OuputFormat>(this->getArg8());  

	switch (ouputFormat){
	case OuputFormat::NEWLINE:
		std::cout << std::endl;
		break;

	case OuputFormat::INT:
		std::cout << this->env.acc.popI() << std::flush;
		break;

	case OuputFormat::UINT:
		std::cout << this->env.acc.popU() << std::flush;
		break;

	case OuputFormat::FLOAT:
		std::cout << this->env.acc.popF() << std::flush;
		break;

	case OuputFormat::STRING:
		const std::uint64_t ptr = this->env.acc.popU();
		std::cout << this->env.heap.access<HeapString>(ptr) << std::endl;
		break;
	}	
}
