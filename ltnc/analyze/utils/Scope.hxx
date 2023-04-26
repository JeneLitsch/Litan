#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "stdxx/reference.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/Namespace.hxx"
#include "Variable.hxx"
#include "Context.hxx"

namespace ltn::c {
	class Scope {
	public:
		virtual std::uint64_t size() const = 0;
		virtual bool is_const() const = 0;
		virtual const Namespace & get_namespace() const = 0;
		virtual std::optional<std::string> get_return() const = 0;
		virtual const type::Type & get_return_type() const = 0;
		virtual const type::Type * resolve_type(const std::string & name) const = 0;
		virtual Context & get_context() const = 0;
		virtual void set_context(stx::reference<Context> context) = 0;

		Variable insert(const std::string & name, const SourceLocation & location, const type::Type & type = type::Any{});
		void set_return(const std::string & return_point);
		void add_type(const std::string & name, const type::Type & type);
		void inherit_types_from(const Scope & scope);
		void inherit_types(auto type_table) {
			for(const auto [alias, type] : type_table) {
				this->type_map.insert({alias,type});
			}
		}

		virtual stx::optref<const Variable> resolve_variable(const std::string & name, const SourceLocation & location) const = 0;
		stx::optref<const ast::Functional> resolve_function(const std::string & name, const Namespace & ns, std::size_t arity) const;
		stx::optref<const sst::Global> resolve_global(const std::string & name, const Namespace & ns) const;
		stx::optref<const sst::Definition> resolve_definiton(const std::string & name, const Namespace & ns) const;
		std::uint64_t resolve_member_id(const std::string & name) const;

	protected:
		std::unordered_map<std::string, Variable> vars;
		std::optional<std::string> return_point;
		std::unordered_map<std::string, type::Type> type_map;
	};
}