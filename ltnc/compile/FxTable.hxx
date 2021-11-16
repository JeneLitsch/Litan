#pragma once
#include "FxSignature.hxx"
namespace ltn::c::compile {
	class FxTable {
	public:
		const FxSignature * find(
			const std::string_view name,
			const std::vector<type::Type> & parameters);
		void insert(const FxSignature & fx);
	private:
		std::vector<FxSignature> functions;
	};
}