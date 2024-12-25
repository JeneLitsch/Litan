#include "Global.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"

namespace ltn::c::ast::decl {
	Global::Global(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze)
		: Static{location, name, namespaze} {}



	Global::~Global() {}
}