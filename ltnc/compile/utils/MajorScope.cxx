#include "MajorScope.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/compile/instantiate_type.hxx"

namespace ltn::c {

	MajorScope::MajorScope(
		const ast::Namespace & namespaze,
		bool c0nst) 
	: namespaze { namespaze }, c0nst { c0nst }, return_type{type::Any{}} {}



	const Variable * MajorScope::resolve(
		const std::string & name,
		const SourceLocation &) const{
		
		if(this->vars.contains(name)) {
			return &this->vars.at(name);
		}
		return nullptr;
	}



	const type::Type * MajorScope::resolve_type(const std::string & name) const {
		if(this->type_map.contains(name)) return &this->type_map.at(name);
		return nullptr;
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

	const type::Type & MajorScope::get_return_type() const  {
		return this->return_type;
	}


	void MajorScope::set_return_type(type::Type type) {
		this->return_type = type;
	}
}