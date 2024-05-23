#include "MajorScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {

	MajorScope::MajorScope(
		const Namespace & namespaze,
		Qualifiers qualifiers,
		stx::reference<Context> context) 
		: namespaze { namespaze }
		, qualifiers { qualifiers }
		, context{context} {}



	stx::optref<const Variable> MajorScope::resolve_local_variable(
		const std::string & name,
		const SourceLocation &) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		return stx::nullref;
	}



	bool MajorScope::is_const() const {
		return this->qualifiers.is_const;
	}



	bool MajorScope::is_coroutine() const {
		return this->qualifiers.is_coroutine;
	}



	const Namespace & MajorScope::get_namespace() const {
		return this->namespaze;
	}



	// size of all stacked scopes combined
	std::uint64_t MajorScope::size() const {
		return this->vars.size();
	}



	std::optional<std::string> MajorScope::get_return() const {
		return this->return_point;
	}


	Context & MajorScope::get_context() const {
		return *this->context;
	}
}