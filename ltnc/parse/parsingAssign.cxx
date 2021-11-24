#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;

		template<class To, class From>
		std::unique_ptr<To> unique_cast_if(std::unique_ptr<From> & from) {
			if(auto ptr_to = dynamic_cast<To*>(from.get())) {
				from.release();
				return std::unique_ptr<To>(ptr_to);
			}
			return nullptr;
		}
	}
	
	std::unique_ptr<ast::Expression> assign(lex::Lexer & lexer) {
		auto expr = expression(lexer);
		if(auto r = assignR(lexer)) {
			if(auto l = unique_cast_if<ast::Assignable>(expr)) {
				return std::make_unique<ast::Assign>(
					std::move(l),
					std::move(r),
					lexer.debug());
			}
			throw CompilerError{
				"Left side of an assignment must be an assignable value",
				lexer.inLine()};
		}
		return expr;
	}

	std::unique_ptr<ast::Expression> assignR(lex::Lexer & lexer) {
		if(lexer.match(TT::ASSIGN)) {
			return expression(lexer);
		}
		return nullptr;
	}
}