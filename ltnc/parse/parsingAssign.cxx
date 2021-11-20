#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	std::unique_ptr<ast::Expression> assign(lex::Lexer & lexer) {
		auto l = expression(lexer);
		if(auto r = assignR(lexer)) {
			return std::make_unique<ast::Assign>(std::move(l), std::move(r), lexer.debug());
		}
		return l;
	}

	std::unique_ptr<ast::Expression> assignR(lex::Lexer & lexer) {
		if(lexer.match(TT::ASSIGN)) {
			return expression(lexer);
		}
		return nullptr;
	}

}