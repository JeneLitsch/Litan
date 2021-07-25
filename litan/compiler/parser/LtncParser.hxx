#pragma once
#include "LtncToken.hxx"
#include "LtncAst.hxx"
namespace ltnc {
	class Parser {
	public:
		Parser();
		std::shared_ptr<Program> parse(const std::vector<Token> & tokens) const;
	};
}