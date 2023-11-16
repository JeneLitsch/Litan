#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "ltn/unique.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Namespace.hxx"
#include "Declaration.hxx"
#include "ltnc/sst/misc/Except.hxx"

namespace ltn::c::sst::expr {
	struct Var;
}

namespace ltn::c::sst::decl {
	struct Function : public Declaration {
		Function(
			const std::string & name,
			Namespace namespaze,
			stmt_ptr && body,
			const Label & label);

		const std::string & get_resolve_name() const;
		const Namespace & get_resolve_namespace() const;
		
		virtual ~Function();

		bool is_const = false;
		bool is_private = false;
		bool is_extern = false;

		Label label;

		stmt_ptr body;
		std::unique_ptr<misc::Except> except;
		std::vector<std::unique_ptr<expr::Var>> capture;
	};

	std::unique_ptr<Function> function(
		const std::string & name,
		Namespace namespaze,
		stmt_ptr && body,
		const Label & label);
}