#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "ltn/unique.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Namespace.hxx"
#include "Declaration.hxx"

namespace ltn::c::sst::expr {
	struct Var;
}

namespace ltn::c::sst {
	struct Parameter {
		std::string name;
	};
	using Parameters = std::vector<Parameter>;



	inline std::string mangle(
		const std::string & name,
		const Namespace & namespaze,
		const Parameters & parameters) {
		std::ostringstream oss;
		oss << namespaze.to_string();
		oss << name << "(";
		oss << std::size(parameters) << ")";
		return oss.str();
	}



	struct Except final : public Node {
		Except(const std::string & errorname, stmt_ptr && body);
		virtual ~Except();
		stmt_ptr body;
		std::string errorname;
	};


	struct Function : public Declaration {
		Function(
			const Label & label,
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			stmt_ptr && body);

		const std::string & get_resolve_name() const;
		const Namespace & get_resolve_namespace() const;
		
		virtual ~Function();

		Parameters parameters;
		bool is_const = false;
		bool is_private = false;
		bool is_extern = false;

		Label label;

		stmt_ptr body;
		std::unique_ptr<Except> except;
		std::vector<std::unique_ptr<expr::Var>> capture;

	};
}