#include "Declaration.hxx"
#include "ltnc/ast/expr/Expression.hxx"

namespace ltn::c::ast::decl {
	Definition::Definition(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze)
		: Static{location, name, namespaze} {}
	Definition::~Definition() {}


	Global::Global(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze)
		: Static{location, name, namespaze} {}
	Global::~Global() {}
}