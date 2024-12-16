#pragma once
#include <iostream>
#include <functional>
#include <initializer_list>
#include "stdxx/json.hxx"
#include "ltnvm/Exception.hxx"
#include "VMCore.hxx"
#include "ltn/cxx_types.hxx"

namespace ltn::vm {
	class VM {
	public:
		VM() {}
		VM(const VM &) = delete;
		VM(VM &&) = delete;
		VM & operator=(const VM &) = delete;
		VM & operator=(VM &&) = delete;
		
		void setup(std::span<const std::uint8_t> code);

		Any call(
			const std::string & function_label,
			const std::vector<Any> & args);

	private:
		Any call(
			const std::string & function_label,
			std::size_t argc,
			const Any * argv);

		VMCore core;
		std::span<const std::uint8_t> byte_code;
	};

	Value run_core(VMCore & core);
}