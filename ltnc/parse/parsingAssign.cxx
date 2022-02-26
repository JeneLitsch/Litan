#include "parsing.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = lex::Token::Type;
		using MT = ast::Modify::Type;

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
		// try parsing assigment
		if(auto r = assignR(lexer)) {
			// ensure left side is assingable
			if(auto l = unique_cast_if<ast::Assignable>(expr)) {
				return std::make_unique<ast::Assign>(
					std::move(l),
					std::move(r),
					lexer.location());
			}
			throw CompilerError{
				"Left side of an assignment must be an assignable expression",
				lexer.location()};
		}
		auto modifyTable = std::array{
			std::pair{MT::ADD,     TT::ASSIGN_ADD},
			std::pair{MT::SUB,     TT::ASSIGN_SUB},
			std::pair{MT::MLT,     TT::ASSIGN_MLT},
			std::pair{MT::DIV,     TT::ASSIGN_DIV},
			std::pair{MT::MOD,     TT::ASSIGN_MOD},
			std::pair{MT::SHIFT_L, TT::ASSIGN_SHIFT_L},
			std::pair{MT::SHIFT_R, TT::ASSIGN_SHIFT_R},
		};
		for(auto [mt, tt] : modifyTable) {
			if(lexer.match(tt)) {
				if(auto l = unique_cast_if<ast::Assignable>(expr)) {
					auto r = expression(lexer);
					return std::make_unique<ast::Modify>(
						mt, std::move(l), std::move(r), lexer.location());
				}
				throw CompilerError{
					"Left side of an assignment must be an assignable expression",
					lexer.location()};
			}
		}
		return expr;
	}

	// Tries parsing assignment after and including =
	std::unique_ptr<ast::Expression> assignR(lex::Lexer & lexer) {
		if(lexer.match(TT::ASSIGN)) {
			return expression(lexer);
		}
		return nullptr;
	}
}