#pragma once
#include <optional>
#include <iostream>
#include <span>
#include <queue>
#include "stdxx/array.hxx"
#include "stdxx/queue.hxx"
#include "stdxx/oop.hxx"
#include "Token.hxx"
#include "ltnc/SourceLocation.hxx"
#include "ltnc/Reporter.hxx"
#include "ltnc/Source.hxx"

namespace ltn::c {

	using Tokens = stx::closed_queue<lex::Token>;

	Tokens lex_sources(std::vector<Source> sources, Reporter & reporter);

	std::optional<lex::Token> match(lex::Token::Type type, Tokens & tokens);
	void sync(Tokens & tokens);
	const SourceLocation & location(const Tokens & tokens);
}