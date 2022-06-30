#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "ltnc/SourceLocation.hxx"
#include "ltnc/ast/Namespace.hxx"
#include "Variable.hxx"
namespace ltn::c::compile {


	class Scope {
	public:
		Scope(const ast::Namespace & namespaze, bool c0nst);
		Scope(const Scope * parent);
		Variable resolve(const std::string & name, const SourceLocation & location) const;
		Variable insert(const std::string & name, Variable::Qualifier qualifier, const SourceLocation & location);
		Variable insert(const std::string & name, const SourceLocation & location);
		const ast::Namespace & get_namespace() const;
		std::uint64_t recSize() const;
		std::optional<std::string> get_return() const;
		void set_return(const std::string & return_point);
		bool is_const() const;
	private:
		std::unordered_map<std::string, Variable> vars;
		std::optional<std::string> return_point;
		const Scope * parent;
		const ast::Namespace & namespaze;
		bool c0nst = false;
	};
}