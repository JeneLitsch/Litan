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
		
		void setup(std::span<const std::uint8_t> code);
		
		Variant run(
			const std::vector<std::string> & args = {},
			const std::string & main = "");

		void register_function(std::int64_t addr, auto fx) {
			core.externals.emplace(addr, ext::Callable{fx});
		}

		void register_function(std::string name, auto fx) {
			auto & link_table = core.dynamic_link_table; 
			if(!link_table.contains(name)) throw std::runtime_error{
				"Cannot link function " + name 
			};
			const auto addr = link_table.at(name); 
			this->register_function(addr, std::move(fx));
		}

		void set_global(
			const std::string & name,
			Variant value);
	
	private:
		VmCore core;
	};
}