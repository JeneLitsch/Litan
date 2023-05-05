#include "MajorScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {

	MajorScope::MajorScope(
		const Namespace & namespaze,
		bool c0nst,
		stx::reference<Context> context) 
		: namespaze { namespaze }
		, c0nst { c0nst }
		, context{context} {}



	stx::optref<const Variable> MajorScope::resolve_variable(
		const std::string & name,
		const SourceLocation &) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		return stx::nullref;
	}



	bool MajorScope::is_const() const {
		return this->c0nst;
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


	void MajorScope::set_context(stx::reference<Context> context) {
		this->context = context;
	}
}