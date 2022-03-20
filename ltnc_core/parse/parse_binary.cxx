#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Binary::Type;


		template<typename op_table, auto presedence_down>
		ast::expr_ptr binary(lex::Lexer & lexer) {
			
			auto l = presedence_down(lexer);
			while (auto op = match_op(lexer, op_table::data)) {
				auto && r = presedence_down(lexer);
				auto expr = std::make_unique<ast::Binary>(
					*op,
					std::move(l),
					std::move(r),
					lexer.location());
				l = std::move(expr);
			}				
			return l;
		}

	}

	namespace {
		struct term_table {
			static const inline auto data = std::array {
				std::pair{TT::PLUS,          OP::ADD},
				std::pair{TT::MINUS,         OP::SUB},
			};
		};



		struct factor_table {
			static const inline auto data = std::array {
				std::pair{TT::STAR, OP::MLT},
				std::pair{TT::SLASH, OP::DIV},
				std::pair{TT::PERCENT, OP::MOD},
			};
		};



		struct shift_table {
			static const inline auto data = std::array {
				std::pair{TT::SHIFT_L,       OP::SHIFT_L},
				std::pair{TT::SHIFT_R,       OP::SHIFT_R},
			};
		};



		struct comparision_table {
			static const inline auto data = std::array {
				std::pair{TT::SMALLER,       OP::SMALLER},
				std::pair{TT::SMALLER_EQUAL, OP::SMALLEREQUAL},
				std::pair{TT::BIGGER,        OP::BIGGER},
				std::pair{TT::BIGGER_EQUAL,  OP::BIGGEREQUAL},
			};
		};


		struct equality_table {
			static const inline auto data = std::array {
				std::pair{TT::EQUAL,         OP::EQUAL},
				std::pair{TT::UNEQUAL,       OP::UNEQUEL},
				std::pair{TT::TILDEx2,       OP::APPROX},
				std::pair{TT::XMARK_TILDE,   OP::NOTPROX},
			};
		};


		struct spaceship_table {
			static const inline auto data = std::array {
				std::pair{TT::SPACE_SHIP,    OP::SPACE_SHIP},
			};
		};


		struct log_or_table {
			static const inline auto data = std::array {
				std::pair{TT::OR, OP::OR}
			};
		};


		struct log_and_table {
			static const inline auto data = std::array {
				std::pair{TT::AND, OP::AND}
			};
		};



		template<auto presedence_down>
		ast::expr_ptr binary_base(lex::Lexer & lexer) {
			static constexpr auto factor      = binary<factor_table,      presedence_down>;
			static constexpr auto term        = binary<term_table,        factor>;
			static constexpr auto shift       = binary<shift_table,       term>;
			static constexpr auto comparision = binary<comparision_table, shift>;
			static constexpr auto equality    = binary<equality_table,    comparision>;
			static constexpr auto spaceship   = binary<spaceship_table,   equality>;
			static constexpr auto logical_or  = binary<log_or_table,      spaceship>;
			static constexpr auto logical_and = binary<log_and_table,     logical_or>;
			return logical_and(lexer);
		}
	}



	ast::expr_ptr binary(lex::Lexer & lexer) {
		return binary_base<parse::unary>(lexer);
	}

	

	ast::expr_ptr static_binary(lex::Lexer & lexer) {
		return binary_base<parse::static_unary>(lexer);
	}
}

