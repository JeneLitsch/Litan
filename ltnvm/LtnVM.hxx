#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include "memory/Register.hxx"
#include "memory/Stack.hxx"
#include "memory/Heap.hxx"
#include "external/External.hxx"
namespace ltn::vm {
	class LtnVM {
	public:
		LtnVM(std::ostream & ostream = std::cout) : ostream(ostream) {}
		void setup(std::vector<std::uint8_t> code) {
			this->byteCode = code;
			this->pc = 0;
		}

		void run();

		void registerExternal(
			std::int64_t id,
			std::unique_ptr<ext::External> && ext);
	
	private:
		std::uint8_t fetchByte();
		std::uint64_t fetchUint();
		
		void state();

		void add(), sub(), mlt(), div(), mod();
		void eql(), ueql(), sml(), bgr(), bgreql(), smleql();
		void shift_l(), shift_r();
		
		void neg(), n0t(), inc(), dec();

		void newi(),newf(), newu(), truE(), falsE(), null(), ch4r(), elem();
		void char_4(), char_8();

		void jump(), call(), reTurn(), iF(), invoke(), external(), capture(), read_captured();
		
		void newarr(), newstr(), newout(), newin(), newfx(), newClock();

		void read(), write(), scrap(), makevar();
		void at(), at_write();
		void read_x(), write_x();
		void read_0(), read_1(), read_2(), read_3();
		void write_0(), write_1(), write_2(), write_3();

		void out();
		void in_str(), in_line(), in_int(), in_float(), is_eof();

		void min(), max(), round(), floor(), ceil(), abs(), hypot(), sqrt();
		
		void sin(), cos(), tan();
		
		void size(), front(), back();
		void insert_back(), insert_front(), insert();
		void remove_back(), remove_front(), remove();
		
		void to_seconds();

		void typeId();

		void outValue(const Value & value);

		// Runtime
		Stack stack;
		Register reg;
		Heap heap;
		std::uint64_t pc;

		// Persistent
		std::vector<std::uint8_t> byteCode;
		std::reference_wrapper<std::ostream> ostream;
		std::unordered_map<std::int64_t, std::unique_ptr<ext::External>> externals;
	};
}