#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/ast/decl/Enumeration.hxx"

namespace ltn::c {
	std::vector<sst::defn_ptr> analyze_enumeration(const ast::decl::Enumeration & enumeration, std::uint64_t & id) {
		Namespace namespaze = enumeration.namespaze;
		namespaze.push_back(enumeration.name);

		return stx::fx::mapped([&] (const auto & label) {
			return sst::decl::definition(
				label.name, namespaze,
				sst::expr::integer(label.value),
				id++);
		}) (enumeration.labels);
	}
}