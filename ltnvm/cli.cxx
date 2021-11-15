#include "Stack.hxx"
#include "Register.hxx"
#include <iostream>
int main(){
	std::cout << ">> Stack" << "\n";
	ltn::vm::Stack stack;
	stack.pushFrame(2, 42);
	stack.writeF(0, 1337);
	stack.writeF(1, 42);
	stack.pushFrame(2, 420);
	stack.writeF(0, 1);
	stack.writeF(1, 2);
	std::cout << stack.readF(0) << "\n";
	std::cout << stack.readF(1) << "\n";
	stack.popFrame(); 
	std::cout << stack.readF(0) << "\n";
	std::cout << stack.readF(1) << "\n";

	std::cout << ">> Register" << "\n";
	ltn::vm::Register reg;
	reg.pushF(3.0);
	reg.pushI(-4);
	reg.pushU(4);
	std::cout << reg.popU() << "\n";
	std::cout << reg.popI() << "\n";
	std::cout << reg.popF() << "\n";

	return 0;
}
