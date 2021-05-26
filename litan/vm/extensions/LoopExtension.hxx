#pragma once
#include "Environment.hxx"
#include "VMInstructions.hxx"
#include <stack>
namespace ltn{
	class LoopExtension {
	public:	
		LoopExtension(Environment & env) : env(env) {}
		void call(std::uint8_t funct);
		
		// start infinite loop
		void inf();

		// start ranged loop between top values of acc
		// 2 pops()
		void range();

		// stops / breaks loop
		void stop();

		// jump to loop head and start next interation
		void cont();
		
		// get current interation index
		void idx();

		void reset();
	private:
		Environment & env;

		struct Loop {
			Loop(std::uint64_t addr, std::uint64_t start, std::uint64_t end){
				this->addr = addr;
				this->idx = start,
				this->end = end;
			}
			Loop(std::uint64_t addr){
				this->addr = addr;
				this->infinite = true;
			}
			inline bool atEnd() const {
				return !infinite && idx >= end;
			}
			// jump back address
			std::uint64_t addr = 0;
			// curretnr interation
			std::int64_t idx = 0;
			// end index
			std::int64_t end = 0;
			// true if infinte loop
			bool infinite = false;
		};
		std::stack<Loop> loops;
	};
}