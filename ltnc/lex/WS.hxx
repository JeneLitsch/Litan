#pragma once
#include <cctype>
#include <istream>

namespace ltnc::lex {
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