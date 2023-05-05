#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "parse_utils.hxx"
namespace ltn::c {
	namespace {
		using TT = Token::Type;
		using OP = BinaryOp;
	}


	
	template<typename op_table, auto presedence_down>
	ast::expr_ptr generic_binary(Tokens & tokens) {
		auto l = presedence_down(tokens);
		while (auto op = match_op(tokens, op_table::data)) {
			auto && r = presedence_down(tokens);
			auto expr = std::make_unique<ast::Binary>(
				*op,
				std::move(l),
				std::move(r),
				location(tokens));
			l = std::move(expr);
		}				
		return l;
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
		ast::expr_ptr binary_base(Tokens & tokens) {
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

			static constexpr auto logical_and = generic_binary<log_and_table,     bit_or>;
			static constexpr auto logical_or  = generic_binary<log_or_table,      logical_and>;
			return logical_or(tokens);
		}
	}



	ast::expr_ptr parse_binary(Tokens & tokens) {
		return binary_base<parse_unary>(tokens);
	}
}

