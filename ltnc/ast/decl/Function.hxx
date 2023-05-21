#pragma once

#include <tuple>
#include <vector>
#include <sstream>
#include "ltn/unique.hxx"
#include "ltnc/Namespace.hxx"
#include "ltnc/ast/decl/Declaration.hxx"

namespace ltn::c::ast {
	class Statement;
	struct Parameter {
		std::string name;
		bool is_variadic;
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
		Except(
			const std::string & errorname,
			std::unique_ptr<Statement> && body,
			const SourceLocation & location)
			: Node(location)
			, body(std::move(body))
			, errorname(errorname) {}
		virtual ~Except() = default;
		std::unique_ptr<Statement> body;
		std::string errorname;
	};



	struct Functional : public Declaration {
		Functional(
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			const SourceLocation & location)
			: Declaration(location, name, namespaze)
			, parameters(std::move(parameters)) {}
		virtual ~Functional() = default;

		Parameters parameters;
		bool is_const = false;
		bool is_private = false;
		bool is_extern = false;

		const std::string & get_resolve_name() const {
			return this->name;
		}

		const Namespace & get_resolve_namespace() const {
			return this->namespaze;
		}
	};



	struct Function final : public Functional {
		Function(
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			std::unique_ptr<Statement> body,
			const SourceLocation & location)
			: Functional{name, namespaze, std::move(parameters), location}
			, body(std::move(body)) {}

		virtual ~Function() = default;
		std::unique_ptr<Statement> body;
		std::unique_ptr<Except> except;
	};



	struct BuildIn final : public Functional {
		BuildIn(
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			const std::string & key,
			const SourceLocation & location)
			: Functional{name, namespaze, std::move(parameters), location}
			, key(key) {}
		virtual ~BuildIn() = default;
		std::string key;		
	};
}