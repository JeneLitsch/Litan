#pragma once
#include "Stack.hxx"
#include "Register.hxx"
#include <iostream>
#include <functional>
#include "Heap.hxx"
namespace ltn::vm {
	class LtnVM {
	public:
		LtnVM(std::ostream & ostream = std::cout) : ostream(ostream) {}
		void setup(std::vector<std::uint8_t> code) {
			this->byteCode = code;
			this->pc = 0;
		}
		void run() { exec(); };
	private:
		std::uint8_t fetchByte();
		std::uint64_t fetchUint();

		void exec();
		
		void add(), sub(), mlt(), div(), mod();
		void eql(), ueql(), sml(), bgr(), bgreql(), smleql();
		
		void neg(), n0t(), inc(), dec();

		void newi(), newf(), newu(), addr(), truE(), falsE(), newarr(), newstr(), null(), ch4r(), elem();

		void jump(), call(), reTurn(), iF(), error();

		void read(), write(), scrap(), makevar();

		void out();

		void outValue(const Value & value);

		Stack stack;
		Register reg;
		Heap heap;
		std::reference_wrapper<std::ostream> ostream;
		std::vector<std::uint8_t> byteCode;
		std::uint64_t pc;
	};
}