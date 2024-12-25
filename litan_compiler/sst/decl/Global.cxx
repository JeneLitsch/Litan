#include "Global.hxx"
#include "litan_compiler/sst/expr/Expression.hxx"

namespace ltn::c::sst::decl {
	Global::Global(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id)
		: Static{name, namespaze, id}
		, expr{std::move(expr)} {}



	Global::~Global() {}



	std::unique_ptr<Global> variable(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id) {
		
		return std::make_unique<Global>(name, namespaze, std::move(expr), id);
	}
}