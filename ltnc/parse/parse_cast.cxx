#include "parse.hxx"

namespace ltn::c {
	using TT = Token::Type;
	using Op = ast::TypedUnary::Op;

	namespace {
		template<Op op, TT tt>
		ast::expr_ptr parse_copy(Tokens & tokens) {
			if(auto t = match(tt, tokens)) {
				BraceTracker brace_tracker;
				open_chevron(tokens, brace_tracker);
				const auto type = parse_type(tokens, brace_tracker);
				close_chevron(tokens, brace_tracker);
				brace_tracker.finalize();
				if(!match(TT::PAREN_L, tokens)) throw CompilerError{
					"Expected ( after static_cast<...>"
				};
				auto expr = parse_expression(tokens);
				if(!match(TT::PAREN_R, tokens)) throw CompilerError{
					"Expected ) after static_cast<...>"
				};
				return std::make_unique<ast::TypedUnary>(
					op,
					type,
					std::move(expr),
					t->location
				);
			}
			else return nullptr;
		}
	}


	ast::expr_ptr parse_static_copy(Tokens & tokens) {
		return parse_copy<Op::STATIC_COPY, TT::STATIC_COPY>(tokens);
	}



	ast::expr_ptr parse_dynamic_copy(Tokens & tokens) {
		return parse_copy<Op::DYNAMIC_COPY, TT::DYNAMIC_COPY>(tokens);
	}
}