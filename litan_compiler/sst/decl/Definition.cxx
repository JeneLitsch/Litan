#include "Definition.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"

namespace ltn::c::sst::decl {
	Definition::Definition(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id)
		: Static{name, namespaze, id}
		, expr{std::move(expr)} {}



	Definition::~Definition() {}



	std::unique_ptr<Definition> definition(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id) {
		
		return std::make_unique<Definition>(name, namespaze, std::move(expr), id);
	}
}