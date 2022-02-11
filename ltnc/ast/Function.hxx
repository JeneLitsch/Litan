#pragma once

#include <tuple>
#include <vector>
#include "Declaration.hxx"
#include "Statement.hxx"
#include "Namespace.hxx"

namespace ltn::c::ast {
	struct Statement;
	using Parameters = std::vector<std::string>;

	struct Except : public Node {
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
			Namespace nameSpace,
			Parameters parameters,
			const SourceLocation & location)
			:	Declaration(location),
				name(name),
				nameSpace(nameSpace),
				parameters(parameters) {}
		virtual ~Functional() = default;
		std::string name;
		Namespace nameSpace;
		Parameters parameters;
	};

	struct Function : public Functional {
		Function(
			const std::string & name,
			Namespace nameSpace,
			Parameters parameters,
			std::unique_ptr<Statement> && body,
			const SourceLocation & location)
			:	Functional(name, nameSpace, parameters, location),
				body(std::move(body)) {}
		virtual ~Function() = default;
		std::unique_ptr<Statement> body;
		std::unique_ptr<Except> except;
	};

	struct Asm : public Functional {
		Asm(
			const std::string & name,
			Namespace nameSpace,
			Parameters parameters,
			const std::vector<std::string> & instructions,
			const SourceLocation & location)
			:	Functional(name, nameSpace, parameters, location),
				instructions(instructions) {}
		virtual ~Asm() = default;
		std::vector<std::string> instructions;		
	};
}