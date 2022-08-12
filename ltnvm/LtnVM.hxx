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
		
		void setup(std::vector<std::uint8_t> code);
		
		Variant run(
			const std::vector<std::string> & args = {},
			const std::string & main = "");

		void register_external(
			std::int64_t id,
			std::unique_ptr<ext::External> && ext);

		void set_global(
			const std::string & name,
			Variant value);
	
	private:
		VmCore core;
	};
}