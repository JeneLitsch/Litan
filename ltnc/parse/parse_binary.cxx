#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Binary::Type;
	}

	namespace {
		struct term_table {
			static const inline auto data = std::array {
				std::pair{TT::PLUS,          OP::ADD},
				std::pair{TT::MINUS,         OP::SUB},
			};
		};



		struct power_table {
			static const inline auto data = std::array {
				std::pair{TT::STARx2,        OP::POW},
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



		struct spaceship_table {
			static const inline auto data = std::array {
				std::pair{TT::SPACE_SHIP,    OP::SPACE_SHIP},
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


		
		struct bitand_table {
			static const inline auto data = std::array {
				std::pair{TT::AMPERSAND, OP::BIT_AND}
			};
		};



		struct bitxor_table {
			static const inline auto data = std::array {
				std::pair{TT::BIT_XOR, OP::BIT_XOR}
			};
		};



		struct bitor_table {
			static const inline auto data = std::array {
				std::pair{TT::BIT_OR, OP::BIT_OR}
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
			static constexpr auto power       = generic_binary<power_table,       presedence_down>;
			static constexpr auto factor      = generic_binary<factor_table,      power>;
			static constexpr auto term        = generic_binary<term_table,        factor>;
			static constexpr auto shift       = generic_binary<shift_table,       term>;
			static constexpr auto spaceship   = generic_binary<spaceship_table,   shift>;
			static constexpr auto comparision = generic_binary<comparision_table, spaceship>;
			static constexpr auto equality    = generic_binary<equality_table,    comparision>;

			static constexpr auto bit_and     = generic_binary<bitand_table,      equality>;
			static constexpr auto bit_xor     = generic_binary<bitxor_table,      bit_and>;
			static constexpr auto bit_or      = generic_binary<bitor_table,       bit_xor>;

			static constexpr auto logical_or  = generic_binary<log_or_table,      bit_or>;
			static constexpr auto logical_and = generic_binary<log_and_table,     logical_or>;
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

