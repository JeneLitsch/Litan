#pragma once
#include "EnumSignature.hxx"
#include <vector>
namespace ltn::c::compile {
	// Holds and resolves functions at compile time
	class EnumTable {
	public:
		const EnumSignature * resolve(
			const std::string_view name,
			const ast::Namespace & from,
			const ast::Namespace & to);

		const EnumSignature * resolve(
			const std::string_view name,
			const ast::Namespace & full);

		void insert(const EnumSignature & fx);
	private:
		std::vector<EnumSignature> enums;
	};
}