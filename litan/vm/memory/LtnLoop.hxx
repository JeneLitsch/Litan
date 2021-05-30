#pragma once
#include <stack>
#include "LtnInstructions.hxx"
#include "LtnEnvironment.hxx"
namespace ltn{
	struct Loop {
		Loop(std::uint64_t addr, std::int64_t start, std::int64_t end){
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
}
