#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include "stdxx/reference.hxx"
#include "litan_compiler/SourceLocation.hxx"
#include "litan_compiler/Namespace.hxx"
#include "Variable.hxx"
#include "litan_compiler/analyze/utils/Context.hxx"

namespace ltn::c {
	class Scope {
	public:
		virtual std::uint64_t size() const = 0;
		virtual bool is_const() const = 0;
		virtual bool is_coroutine() const = 0;
		virtual const Namespace & get_namespace() const = 0;
		virtual std::optional<std::string> get_return() const = 0;
		virtual Context & get_context() const = 0;
		void set_return(const std::string & return_point);

		virtual Variable declare_variable(const std::string & name, const SourceLocation & location) = 0;

		virtual stx::optref<const Variable> resolve_local_variable(const std::string & name, const SourceLocation & location) const = 0;
		
		stx::optref<const ast::decl::Function> resolve_function(const std::string & name, const Namespace & ns, std::size_t arity, VariadicMode var_mode = VariadicMode::PROHIBITED) const;
		stx::optref<const sst::decl::Global> resolve_global_variable(const std::string & name, const Namespace & ns) const;
		stx::optref<const sst::decl::Definition> resolve_definiton(const std::string & name, const Namespace & ns) const;
		std::uint64_t resolve_member_id(const std::string & name) const;
		sst::expr_ptr resolve_custom_literal(const std::string & type, const std::string & value) const;

		void require_function(stx::reference<const ast::decl::Function> fx);
		void require_function(StagedFunction staged);

		const std::vector<const ast::decl::Function *> & get_all_functions() const;

	protected:
		std::optional<std::string> return_point;
	};
}