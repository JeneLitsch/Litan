#pragma once

#include "Node.hxx"
#include <vector>
#include <tuple>

namespace ltnc::ast {
	class Statement;
	struct Function : public Node {
		Function(
			const std::string & name,
			const std::string & returnType,
			const std::vector<std::tuple<std::string, std::string>> & parameters,
			std::unique_ptr<Statement> && body)
			:	name(name),
				returnType(returnType),
				parameters(parameters),
				body(std::move(body)) {}
		std::string name;
		std::string returnType;
		std::vector<std::tuple<std::string, std::string>> parameters;
		std::unique_ptr<Statement> body;
	};
}