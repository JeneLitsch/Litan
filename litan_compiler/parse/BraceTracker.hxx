#pragma once
#include <cstdint>
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/tokens/Token.hxx"

namespace ltn::c {
	class BraceTracker {
	public:
		void open();
		void found_closed(std::int64_t count);
		void close();
		void finalize();

	private:
		std::int64_t opened_braces = 0;
		std::int64_t found_closed_braces = 0;
	};


	void open_chevron(Tokens & tokens, BraceTracker & brace_tracker);
	void close_chevron(Tokens & tokens, BraceTracker & brace_tracker);
}
