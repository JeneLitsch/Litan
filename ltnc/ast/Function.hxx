#pragma once

#include <tuple>
#include <vector>
#include "Declaration.hxx"
#include "Statement.hxx"
#include "Namespace.hxx"

namespace ltn::c::ast {
	class Statement;
	using Parameters = std::vector<std::string>;

	struct Functional : public Declaration {
		Functional(
			const std::string & name,
			Namespace nameSpace,
			Parameters parameters,
			const lex::DebugInfo & debugInfo)
			:	Declaration(debugInfo),
				name(name),
				nameSpace(nameSpace),
				parameters(parameters) {}
		virtual ~Functional() = default;
		const std::string name;
		Namespace nameSpace;
		const Parameters parameters;
	};

	struct Function : public Functional {
		Function(
			const std::string & name,
			Namespace nameSpace,
			Parameters parameters,
			std::unique_ptr<Statement> && body,
			const lex::DebugInfo & debugInfo)
			:	Functional(name, nameSpace, parameters, debugInfo),
				body(std::move(body)) {}
		virtual ~Function() = default;
		const std::unique_ptr<Statement> body;
	};

	struct Asm : public Functional {
		Asm(
			const std::string & name,
			Namespace nameSpace,
			Parameters parameters,
			const std::vector<std::string> & instructions,
			const lex::DebugInfo & debugInfo)
			:	Functional(name, nameSpace, parameters, debugInfo),
				instructions(instructions) {}
		virtual ~Asm() = default;
		std::vector<std::string> instructions;		
	};
}