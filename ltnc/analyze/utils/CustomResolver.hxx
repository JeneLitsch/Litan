#pragma once
#include <map>
#include "stdxx/functional.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	class CustomResolver {
	public:
		CustomResolver();
		sst::expr_ptr resolve(
			const std::string & type,
			const std::string & value);

	private:
		std::map<std::string, std::function<sst::expr_ptr(const std::string &)>> table;
	};
}