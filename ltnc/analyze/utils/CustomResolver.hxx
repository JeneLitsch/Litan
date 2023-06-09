#pragma once
#include <map>
#include "stdxx/functional.hxx"
#include "ltnc/sst/SST.hxx"
#include "CustomLiteral.hxx"

namespace ltn::c {
	class CustomResolver {
	public:
		CustomResolver(const std::vector<CustomLiteral> & literals);
		sst::expr_ptr resolve(
			const std::string & type,
			const std::string & value);

	private:
		std::map<std::string, CustomLiteral> table;
	};
}