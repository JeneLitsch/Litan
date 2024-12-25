#include "Definition.hxx"
#include "litan_compiler/ast/expr/Expression.hxx"

namespace ltn::c::ast::decl {
	Definition::Definition(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze)
		: Static{location, name, namespaze} {}



	Definition::~Definition() {}
}