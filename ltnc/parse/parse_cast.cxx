#include "parse.hxx"

namespace ltn::c {
	using TT = Token::Type;

	namespace {
		template<typename Node, TT tt>
		ast::expr_ptr parse_cast(Tokens & tokens) {
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
				return std::make_unique<Node>(
					type,
					std::move(expr),
					t->location
				);
			}
			else return nullptr;
		}
	}


	ast::expr_ptr parse_static_cast(Tokens & tokens) {
		return parse_cast<ast::StaticCast, TT::STATIC_CAST>(tokens);
	}



	ast::expr_ptr parse_dynamic_cast(Tokens & tokens) {
		return parse_cast<ast::DynamicCast, TT::DYNAMIC_CAST>(tokens);
	}
}