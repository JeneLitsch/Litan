#include "Static.hxx"

namespace ltn::c::sst::decl {
	Static::Static(
		const std::string & name,
		const Namespace & namespaze,
		std::uint64_t id)
		: Declaration(name, namespaze)
		, id{id} {}
	
	
	
	const std::string & Static::get_resolve_name() const {
		return this->name;
	}



	const Namespace & Static::get_resolve_namespace() const {
		return this->namespaze;
	}
}