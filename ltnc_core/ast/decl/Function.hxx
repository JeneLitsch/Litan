#pragma once

#include <tuple>
#include <vector>
#include "Declaration.hxx"
#include "../Namespace.hxx"

namespace ltn::c::ast {
	struct Statement;
	using Parameters = std::vector<std::string>;



	struct Except final : public Node {
		Except(
			const std::string & errorname,
			std::unique_ptr<Statement> && body,
			const SourceLocation & location)
			:	Node(location),
				body(std::move(body)),
				errorname(errorname) {}
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
			:	Declaration(location, name, namespaze),
				parameters(parameters) {}
		virtual ~Functional() = default;

		Parameters parameters;
	};



	struct Function final : public Functional {
		Function(
			const std::string & name,
			Namespace namespaze,
			Parameters parameters,
			std::unique_ptr<Statement> && body,
			const SourceLocation & location)
			:	Functional(name, namespaze, parameters, location),
				body(std::move(body)) {}
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
			:	Functional(name, namespaze, parameters, location),
				key(key) {}
		virtual ~BuildIn() = default;
		std::string key;		
	};
}