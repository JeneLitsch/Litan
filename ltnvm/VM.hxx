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
		
		Any run(
			const std::vector<std::string> & args = {},
			const std::string & main = "");

		Any call(
			const std::string & function_label,
			const std::vector<Any> & args);

		Any call(
			const std::string & function_label,
			const std::initializer_list<Any> & args);

		void register_function(std::int64_t address, auto fx) {
			core.fx_table_ltn_to_cxx.emplace(address, ext::Callable{std::move(fx)});
		}

		void set_global(
			const std::string & name,
			Any value);

		void set_globals(const stx::json::iterator & iter);

		bool has_function(const std::string & fx_name);
	
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