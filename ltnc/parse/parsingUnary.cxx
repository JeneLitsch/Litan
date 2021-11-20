#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;

		std::unique_ptr<ast::Expression> index(lex::Lexer & lexer) {
			if(lexer.match(TT::BRACKET_L)) {
				auto index = expression(lexer);
				if(lexer.match(TT::BRACKET_R)) {
					return index;
				}
				throw CompilerError{"Missing ]", lexer.inLine()};
			}
			return nullptr;
		}

		std::unique_ptr<ast::Expression> unaryR(
			lex::Lexer & lexer,
			std::unique_ptr<ast::Expression> l) {
			
			if(auto index = parse::index(lexer)) {
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					index->debugInfo);
				return unaryR(lexer, std::move(full));
			}
			return l;
		}
	}


	std::unique_ptr<ast::Expression> unary(lex::Lexer & lexer) {
		if(lexer.match(TT::MINUS)) {
			return std::make_unique<ast::Unary>(OP::NEG, unary(lexer), lexer.debug());
		}
		if(lexer.match(TT::NOT)) {
			return std::make_unique<ast::Unary>(OP::NOT, unary(lexer), lexer.debug());
		}
		return unaryR(lexer, parse::primary(lexer));
	}
}

