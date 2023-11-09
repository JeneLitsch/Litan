#include "Global.hxx"
#include "ltnc/sst/expr/Expression.hxx"

namespace ltn::c::sst {
	Global::Global(
		const std::string & name,
		const Namespace & namespaze,
		std::unique_ptr<sst::expr::Expression> expr,
		std::uint64_t id)
		: Static{name, namespaze, id}
		, expr{std::move(expr)} {}



	Global::~Global() {}
}