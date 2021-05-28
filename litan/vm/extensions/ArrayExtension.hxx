#pragma once
#include <vector>
#include <cstdint>
#include <stack>
#include <map>
#include <queue>
#include "Environment.hxx"
#include "LtnInstructions.hxx"

namespace ltn{
	// VM Extension for dynamic memory management
	// buffer:: prefix 
	class ArrayExtension {
	public: 
		ArrayExtension(Environment & env);
		void call(std::uint8_t funct);
		inline void reset() {
			this->buffers.clear();
			this->resuseableIDs = std::queue<std::uint64_t>();
			this->nextID = 0;
		}
		void setBuffer(const std::vector<std::uint64_t> & buffer);
	private:
		// instructions
		void nEw(); void del();
		void clr();
		void get(); void set();
		void add(); void pop();
		void len();
		
		// internals
		std::vector<std::uint64_t> & getBuffer(std::uint64_t addr);
		Environment & env;

		std::map<std::uint64_t, std::vector<std::uint64_t>> buffers;
		std::queue<std::uint64_t> resuseableIDs;
		std::uint64_t nextID;
	};
}