#pragma once

#include "Declaration.hxx"
#include "Type.hxx"
#include <vector>
#include <tuple>

namespace ltn::c::ast {
	class Statement;
	using Parameter = std::tuple<std::unique_ptr<ast::Type>, std::string>;
	using Parameters = std::vector<Parameter>;
	struct Function : public Declaration {
		Function(
			const std::string & name,
			std::unique_ptr<Type> && returnType,
			Parameters parameters,
			std::unique_ptr<Statement> && body)
			:	name(name),
				returnType(std::move(returnType)),
				parameters(std::move(parameters)),
				body(std::move(body)) {}
				
		std::string name;
		std::unique_ptr<Type> returnType;
		Parameters parameters;
		std::unique_ptr<Statement> body;
	};
}