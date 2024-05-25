#include "LocalScope.hxx"
#include "ltnc/analyze/error.hxx"

namespace ltn::c {
	LocalVariableInfo LocalScope::declare_local_variable(
		const std::string & name,
		const SourceLocation & location) {
		if(this->vars.contains(name)) {
			throw redefined_variable(name, location);
		}
		const auto address = size();
		const LocalVariableInfo var{
			.address = address,
		}; 
		this->vars.insert({name, var});
		return var;
	}
}