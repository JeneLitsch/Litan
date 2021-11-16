#pragma once
#include "Stack.hxx"
#include "Register.hxx"
#include <iostream>
#include <functional>
namespace ltn::vm {
	class LtnVM {
	public:
		LtnVM(std::ostream & out = std::cout);
		void setup(std::vector<std::uint8_t> byteCode);
	private:
		void exec();
		
		void addi(), subi(), mlti(), divi(), modi();
		void addf(), subf(), mltf(), divf(), modf();

		Stack stack;
		Register reg;
		std::reference_wrapper<std::ostream> out;
		std::vector<std::uint8_t> byteCode;
	};
}