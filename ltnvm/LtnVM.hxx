#pragma once
#include "Stack.hxx"
#include "Register.hxx"
#include <iostream>
#include <functional>
namespace ltn::vm {
	class LtnVM {
	public:
		LtnVM(std::ostream & out = std::cout) : out(out) {}
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
		
		void neg(), n0t();

		void newi(), newf(), newu(), newref(), truE(), falsE(), newarr(), null();

		void jump(), call(), reTurn(), iF(), error();

		void read(), write(), scrap(), makevar();

		void ouT();

		Stack stack;
		Register reg;
		std::reference_wrapper<std::ostream> out;
		std::vector<std::uint8_t> byteCode;
		std::uint64_t pc;
	};
}