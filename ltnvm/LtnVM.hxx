#pragma once
#include <iostream>
#include <functional>
#include "Exception.hxx"
#include "VmCore.hxx"

namespace ltn::vm {
	class LtnVM {
	public:

		LtnVM() {}
		void setup(std::vector<std::uint8_t> code) {
			this->core.byte_code = code;
			this->core.pc = 0;
		}

		Value run(const std::vector<std::string> & args = {});

		void register_external(
			std::int64_t id,
			std::unique_ptr<ext::External> && ext);

		Heap & get_heap() {
			return this->core.heap;
		}

		Register & get_register() {
			return this->core.reg;
		}

		Stack & get_stack() {
			return this->core.stack;
		}

	
	private:
		void error(const std::string & msg);
		VmCore core;
	};
}