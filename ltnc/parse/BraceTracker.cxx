#include "BraceTracker.hxx"

namespace ltn::c {
	using TT = Token::Type;



	void BraceTracker::open() {
		++this->opened_braces;
	}



	void BraceTracker::found_closed(std::int64_t count) {
		this->found_closed_braces += count;
	}
	
	
	
	void BraceTracker::close() {
		if(this->found_closed_braces <= 0) throw CompilerError{"Missing >"};
		if(this->opened_braces <= 0) throw CompilerError{"Unexpected >"};
		--this->opened_braces;
		--this->found_closed_braces;
	}



	void BraceTracker::finalize() {
		if(this->opened_braces < 0) throw CompilerError{"Unexpected >"};
		if(this->opened_braces > 0) throw CompilerError{"Missing >"};
		if(this->found_closed_braces < 0) throw CompilerError{"Missing >"};
		if(this->found_closed_braces > 0) throw CompilerError{"Unexpected >"};
	} 



	void open_chevron(Tokens & tokens, BraceTracker & brace_tracker) {
		if(!match(TT::SMALLER, tokens)) throw CompilerError{"Expected <"};
		brace_tracker.open();
	}



	void close_chevron(Tokens & tokens, BraceTracker & brace_tracker) {
		if(match(TT::BIGGER, tokens)) {
			brace_tracker.found_closed(1);
		}
		if(match(TT::SHIFT_R, tokens)) {
			brace_tracker.found_closed(2);
		}
		brace_tracker.close();
	}
}