#pragma once
#include <iostream>
#include <functional>
#include "ltnvm/Exception.hxx"
#include "VmCore.hxx"
#include "ltn/cxx_types.hxx"

namespace ltn::vm {
	class LtnVM {
	public:
		LtnVM() {}
		LtnVM(const LtnVM &) = delete;
		LtnVM(LtnVM &&) = delete;
		LtnVM & operator=(const LtnVM &) = delete;
		LtnVM & operator=(LtnVM &&) = delete;
		
		void setup(std::span<const std::uint8_t> code);
		
		Any run(
			const std::vector<std::string> & args = {},
			const std::string & main = "");

		Any call(
			const std::string & function_label,
			const std::vector<Any> & args);

		void register_function(std::int64_t address, auto fx) {
			core.fx_table_ltn_to_cxx.emplace(address, ext::Callable{std::move(fx)});
		}

		void set_global(
			const std::string & name,
			Any value);

		bool has_function(const std::string & fx_name);
	
	private:
		VmCore core;
		std::span<const std::uint8_t> byte_code;
	};

	Value run_core(VmCore & core);
}