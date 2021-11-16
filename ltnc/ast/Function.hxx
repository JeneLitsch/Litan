#pragma once

#include "Declaration.hxx"
#include "ltnc/type/Type.hxx"
#include <vector>
#include <tuple>

namespace ltn::c::ast {
	class Statement;
	using Parameter = std::tuple<type::Type, std::string>;
	using Parameters = std::vector<Parameter>;
	struct Function : public Declaration {
		Function(
			const std::string & name,
			const type::Type & returnType,
			Parameters parameters,
			std::unique_ptr<Statement> && body)
			:	name(name),
				returnType(returnType),
				parameters(std::move(parameters)),
				body(std::move(body)) {}
				
		std::string name;
		type::Type returnType;
		Parameters parameters;
		std::unique_ptr<Statement> body;
	};
}