#pragma once
#include "GlobalSignature.hxx"
#include <vector>
namespace ltn::c::compile {
	// Holds and resolves functions at compile time
	class GlobalTable {
	public:
		const GlobalSignature * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to);

		const GlobalSignature * resolve(
			const std::string_view name,
			const ast::Namespace & full);

		void insert(const GlobalSignature & fx);
	private:
		std::vector<GlobalSignature> enums;
	};
}