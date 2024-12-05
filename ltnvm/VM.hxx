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

		void register_function(std::int64_t address, auto fx) {
			core.fx_table_ltn_to_cxx.emplace(address, ext::Callable{std::move(fx)});
		}
	
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