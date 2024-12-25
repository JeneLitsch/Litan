#include "Static.hxx"

namespace ltn::c::ast::decl {
	Static::Static(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze)
		: Declaration(location, name, namespaze)
		, id(++counter) {}
	
	const std::string & Static::get_resolve_name() const {
		return this->name;
	}

	const Namespace & Static::get_resolve_namespace() const {
		return this->namespaze;
	}
}

