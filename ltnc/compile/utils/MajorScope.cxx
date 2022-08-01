#include "MajorScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {

	MajorScope::MajorScope(const ast::Namespace & namespaze, bool c0nst) :
		namespaze { namespaze },
		c0nst { c0nst }
		{}



	Variable MajorScope::resolve(
		const std::string & name,
		const SourceLocation & location) const{
		
		if(this->vars.contains(name)) {
			return this->vars.at(name);
		}
		else throw CompilerError{"Undefined variable " + name, location};
	}



	bool MajorScope::is_const() const {
		return this->c0nst;
	}



	const ast::Namespace & MajorScope::get_namespace() const {
		return this->namespaze;
	}



	// size of all stacked scopes combined
	std::uint64_t MajorScope::size() const {
		return this->vars.size();
	}



	std::optional<std::string> MajorScope::get_return() const {
		return this->return_point;
	}
}