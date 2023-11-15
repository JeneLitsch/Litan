#include "Definition.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst::decl {
	Definition::Definition(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id)
		: Static{name, namespaze, id}
		, expr{std::move(expr)} {}



	Definition::~Definition() {}
}