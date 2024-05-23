#include "LocalScope.hxx"
#include "ltnc/analyze/error.hxx"

namespace ltn::c {
	Variable LocalScope::declare_variable(
		const std::string & name,
		const SourceLocation & location) {
		if(this->vars.contains(name)) {
			throw redefined_variable(name, location);
		}
		const auto address = size();
		const Variable var{
			.address = address,
		}; 
		this->vars.insert({name, var});
		return var;
	}
}