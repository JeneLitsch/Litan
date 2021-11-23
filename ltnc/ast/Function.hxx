#pragma once

#include "Declaration.hxx"
#include "Statement.hxx"
#include <vector>
#include <tuple>

namespace ltn::c::ast {
	class Statement;
	using Parameters = std::vector<std::string>;
	struct Function : public Declaration {
		Function(
			const std::string & name,
			Parameters parameters,
			std::unique_ptr<Statement> && body,
			const lex::DebugInfo & debugInfo)
			:	Declaration(debugInfo),
				name(name),
				parameters(parameters),
				body(std::move(body)) {}
				
		const std::string name;
		const Parameters parameters;
		const std::unique_ptr<Statement> body;
	};
}