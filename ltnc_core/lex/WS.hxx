#pragma once
#include <cctype>
#include <istream>
#include <iostream>

namespace ltn::c::lex {
	// std::ws with newline counting
	struct WS {	std::size_t & line; };

	std::istream & operator>>(std::istream & in, const WS & ws) {
		while(std::isspace(in.peek())) {
			if(in.peek() == '\n') {
				ws.line++;
			}
			in.ignore();
		}
		return in;
	}
}