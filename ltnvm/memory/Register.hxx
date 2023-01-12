#pragma once
#include <vector>
#include <cstdint>
#include <iterator>
#include <iostream>
#include "Value.hxx"

namespace ltn::vm {
	class Register {
	public:


		const std::vector<Value> & get_container() const;

		void reset();
		std::size_t size() const;
	private:
		std::vector<Value> stack;
	};
}