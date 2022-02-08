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
		inline std::uint8_t fetchByte() {
			return byteCode[this->pc++];
		}
	
		inline std::uint64_t fetchUint() {
			std::uint64_t value = 0;
			for(auto i = 0; i < 8; i++) {
				value <<= 8;
				value |= static_cast<std::uint64_t>(byteCode[this->pc++]);
			}
			return value;
		}
		
		void
			state();

		void
			add(),
			sub(),
			mlt(),
			div(),
			mod();
		
		void 
			eql(),
			ueql(),
			sml(),
			bgr(),
			bgreql(),
			smleql();
		
		void
			shift_l(),
			shift_r();
		
		void
			neg(),
			n0t(),
			inc(),
			dec();

		void
			newi(),
			newf(),
			newu(),
			truE(),
			falsE(),
			null(),
			ch4r(),
			elem();
		
		void
			char_4(),
			char_8();

		void
			jump(),
			call(),
			reTurn(),
			iF(),
			invoke(),
			external(),
			algorithm(),
			capture(),
			parameters();
		
		void
			newarr(),
			newstr(),
			newout(),
			newin(),
			newfx(),
			newclock(),
			newstruct(),
			newrange(),
			newstack(),
			newqueue(),
			newmap();

		void
			read(),
			write(),
			scrap(),
			makevar(),
			read_x(),
			write_x(),
			swap();
		
		void
			read_0(),
			read_1(),
			read_2(),
			read_3(),
			write_0(),
			write_1(),
			write_2(),
			write_3();

		void
			out(),
			in_str(),
			in_line(),
			in_int(),
			in_float(),
			is_eof();

		void
			min(),
			max(),
			round(),
			floor(),
			ceil(),
			abs(),
			hypot(),
			sqrt(),
			log(),
			ln(),
			pow();
		
		void
			sin(),
			cos(),
			tan();
		
		void
			size(),
			at(),
			at_write(),
			front(),
			back(),
			insert(),
			remove(),
			begin(),
			end(),
			push(),
			pop(),
			peek(),
			contains();
		
		void
			cast_int(),
			cast_float(),
			cast_string(),
			cast_bool(),
			cast_array();

		void
			typeId(),
			clone();

		void
			member_read(),
			member_write();

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