#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "ltnc/SourceLocation.hxx"
#include "ltnc/ast/Namespace.hxx"
#include "Variable.hxx"

namespace ltn::c {
	class Scope {
	public:
		virtual Variable resolve(const std::string & name, const SourceLocation & location) const = 0;
		virtual std::uint64_t size() const = 0;
		virtual bool is_const() const = 0;
		virtual const ast::Namespace & get_namespace() const = 0;
		virtual std::optional<std::string> get_return() const = 0;

		Variable insert(const std::string & name, const SourceLocation & location, const type::Type & type = type::Any{});
		void set_return(const std::string & return_point);
	protected:
		std::unordered_map<std::string, Variable> vars;
		std::optional<std::string> return_point;
	};
}