#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "ltn/unique.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Namespace.hxx"
#include "Declaration.hxx"
#include "ltnc/sst/misc/Parameter.hxx"
#include "ltnc/sst/misc/Except.hxx"

namespace ltn::c::sst::expr {
	struct Var;
}

namespace ltn::c::sst::decl {
	struct Function : public Declaration {
		Function(
			const Label & label,
			const std::string & name,
			Namespace namespaze,
			misc::Parameters parameters,
			stmt_ptr && body);

		const std::string & get_resolve_name() const;
		const Namespace & get_resolve_namespace() const;
		
		virtual ~Function();

		misc::Parameters parameters;
		bool is_const = false;
		bool is_private = false;
		bool is_extern = false;

		Label label;

		stmt_ptr body;
		std::unique_ptr<misc::Except> except;
		std::vector<std::unique_ptr<expr::Var>> capture;
	};



	inline std::string mangle(
		const std::string & name,
		const Namespace & namespaze,
		const misc::Parameters & parameters) {
		std::ostringstream oss;
		oss << namespaze.to_string();
		oss << name << "(";
		oss << std::size(parameters) << ")";
		return oss.str();
	}
}