#pragma once
#include <iostream>
#include <functional>
#include "Exception.hxx"
#include "VmCore.hxx"
#include "ltn/variant.hxx"

namespace ltn::vm {
	class LtnVM {
	public:
		LtnVM() {}
		LtnVM(const LtnVM &) = delete;
		LtnVM(LtnVM &&) = delete;
		LtnVM & operator=(const LtnVM &) = delete;
		LtnVM & operator=(LtnVM &&) = delete;
		
		void setup(std::span<const std::uint8_t> code);
		
		Variant run(
			const std::vector<String> & args = {},
			const std::string & main = "");

		void register_function(std::int64_t address, auto fx) {
			core.externals.emplace(address, ext::Callable{std::move(fx)});
		}

		void set_global(
			const std::string & name,
			Variant value);
	
	private:
		VmCore core;
		std::span<const std::uint8_t> byte_code;
	};

	Value run_core(VmCore & core);
}