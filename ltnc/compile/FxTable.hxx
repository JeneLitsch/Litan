#pragma once
#include "FxSignature.hxx"
#include <vector>
namespace ltn::c::compile {
	// Holds and resolves functions at compile time
	class FxTable {
	public:
		const FxSignature * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to,
			const std::size_t parameters);

		const FxSignature * resolve(
			const std::string_view name,
			const ast::Namespace & full,
			const std::size_t parameters);

		void insert(const FxSignature & fx);
	private:
		std::vector<FxSignature> functions;
	};
}