#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "litan_core/unique.hxx"
#include "litan_compiler/Label.hxx"
#include "litan_compiler/Namespace.hxx"
#include "litan_compiler/Qualifiers.hxx"
#include "Declaration.hxx"
#include "litan_compiler/sst/misc/Except.hxx"

namespace ltn::c::sst::expr {
	struct Var;
}

namespace ltn::c::sst::decl {
	struct Function : public Declaration {
		Function(
			const std::string & name,
			std::uint8_t arity,
			Namespace namespaze,
			stmt_ptr && body,
			const Label & label);

		const std::string & get_resolve_name() const;
		const Namespace & get_resolve_namespace() const;
		
		virtual ~Function();

		Qualifiers qualifiers;

		Label label;
		std::uint8_t arity;
		bool is_variadic;

		stmt_ptr body;
		std::unique_ptr<misc::Except> except;
		std::vector<std::unique_ptr<expr::Var>> capture;
	};

	std::unique_ptr<Function> function(
		const std::string & name,
		std::uint8_t arity,
		Namespace namespaze,
		stmt_ptr && body,
		const Label & label);
}