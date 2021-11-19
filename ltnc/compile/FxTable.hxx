#pragma once
#include "FxSignature.hxx"
#include <vector>
namespace ltn::c::compile {
	class FxTable {
	public:
		const FxSignature * find(
			const std::string_view name,
			const std::size_t parameters);
		void insert(const FxSignature & fx);
	private:
		std::vector<FxSignature> functions;
	};
}