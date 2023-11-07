#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "ltn/unique.hxx"
#include "ltnc/Label.hxx"
#include "ltnc/Namespace.hxx"
#include "Declaration.hxx"

namespace ltn::c::sst {
	class Statement;
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
		Except(const std::string & errorname, std::unique_ptr<Statement> && body);
		virtual ~Except();
		std::unique_ptr<Statement> body;
		std::string errorname;
	};


	struct Var;
	struct Function : public Declaration {
		Function(
			const Label & label,
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			std::unique_ptr<Statement> && body);

		const std::string & get_resolve_name() const;
		const Namespace & get_resolve_namespace() const;
		
		virtual ~Function();

		Parameters parameters;
		bool is_const = false;
		bool is_private = false;
		bool is_extern = false;

		Label label;

		std::unique_ptr<Statement> body;
		std::unique_ptr<Except> except;
		std::vector<std::unique_ptr<Var>> capture;

	};
}