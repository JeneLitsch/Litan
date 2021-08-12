#pragma once
#include "LtncToken.hxx"
#include "LtncAst.hxx"
#include "LtnErrorReporter.hxx"
namespace ltnc {
	class Parser {
	public:
		Parser();
		std::shared_ptr<Program> parse(
			ltn::ErrorReporter & error,
			const std::vector<Token> & tokens) const;
	};
}