#pragma once
#include <iostream>
#include <functional>
#include <initializer_list>
#include "stdxx/json.hxx"
#include "litan_vm/Exception.hxx"
#include "VMCore.hxx"
#include "litan_core/cxx_types.hxx"

namespace ltn::vm {
	class VM {
	public:
		VM();
		
		void setup(std::span<const std::uint8_t> code);

		Any call(
			const std::string & function_label,
			const std::vector<Any> & args);

	private:
		Any call(
			const std::string & function_label,
			std::size_t argc,
			const Any * argv);

		std::unique_ptr<VMCore> core;
	};

	Value run_core(VMCore & core);
}