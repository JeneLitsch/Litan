#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Unary::Type;
	}

	std::unique_ptr<ast::Type> container(
		lex::Lexer & lexer, const std::string & name) {
		if(!lexer.match(TT::BRACKET_L)) {
			throw CompilerError("expected [", lexer.inLine());	
		}
		auto && contained = type(lexer);
		if(!lexer.match(TT::BRACKET_R)) {
			throw CompilerError("expected ]", lexer.inLine());
		}
		return std::make_unique<ast::TypeContainer>(name, std::move(contained));
	}

	std::unique_ptr<ast::Type> type(lex::Lexer & lexer) {
		if(const auto id = lexer.match(TT::INDENTIFIER)) {
			if(id->str == "Array") {
				return container(lexer, "Array");
			}
			return std::make_unique<ast::TypeName>(id->str);
		}
		else {
			throw CompilerError("expected valid typename", lexer.inLine());
		}
	}
}

