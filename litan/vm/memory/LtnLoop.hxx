#pragma once
#include <stack>
#include "LtnInstructions.hxx"
#include "LtnEnvironment.hxx"
namespace ltn{
	struct Loop {
		Loop(std::uint64_t addr, std::int64_t start, std::int64_t end)
			: end(end), infinite(false){
			this->addr = addr;
			this->idx = start;
		}
		Loop(std::uint64_t addr) 
			: infinite(true){
			this->addr = addr;
		}
		inline bool atEnd() const {
			return !infinite && idx >= end;
		}
		// jump back address
		std::uint64_t addr = 0;
		// curretnr interation
		std::int64_t idx = 0;
		const std::int64_t end = 0;
		const bool infinite = false;
	};
}
