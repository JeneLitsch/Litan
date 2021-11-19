#include "Stack.hxx"
#include "Register.hxx"
#include <iostream>
int main(){
	std::cout << ">> Stack" << "\n";
	ltn::vm::Stack stack;
	stack.pushFrame(2, 42);
	stack.write(0, {1337});
	stack.write(1, {42});
	stack.pushFrame(2, 420);
	stack.write(0, {1});
	stack.write(1, {2});
	std::cout << stack.read(0).i << "\n";
	std::cout << stack.read(1).i << "\n";
	stack.popFrame(); 
	std::cout << stack.read(0).i << "\n";
	std::cout << stack.read(1).i << "\n";

	std::cout << ">> Register" << "\n";
	ltn::vm::Register reg;
	reg.push({3});
	reg.push({5});
	reg.push({4});
	std::cout << reg.pop().i << "\n";
	std::cout << reg.pop().i << "\n";
	std::cout << reg.pop().i << "\n";

	return 0;
}
