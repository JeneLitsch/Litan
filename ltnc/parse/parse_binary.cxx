#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::SimpleBinary::Type;


		template<class ExprType, typename op_table, auto presedence_down>
		ast::expr_ptr binary(lex::Lexer & lexer) {
			
			auto l = presedence_down(lexer);
			while (auto op = match_op(lexer, op_table::data)) {
				auto && r = presedence_down(lexer);
				auto expr = std::make_unique<ExprType>(
					*op,
					std::move(l),
					std::move(r),
					lexer.location());
				l = std::move(expr);
			}				
			return l;
		}

		template<typename op_table, auto presedence_down>
		constexpr auto regular = binary<ast::SimpleBinary, op_table, presedence_down>;

		template<typename op_table, auto presedence_down>
		constexpr auto logical = binary<ast::Logical, op_table, presedence_down>;
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
				std::pair{TT::OR, ast::Logical::Type::OR}
			};
		};


		struct log_and_table {
			static const inline auto data = std::array {
				std::pair{TT::AND, ast::Logical::Type::AND}
			};
		};



		template<auto presedence_down>
		ast::expr_ptr binary_base(lex::Lexer & lexer) {
			static constexpr auto factor      = regular<factor_table,      presedence_down>;
			static constexpr auto term        = regular<term_table,        factor>;
			static constexpr auto shift       = regular<shift_table,       term>;
			static constexpr auto comparision = regular<comparision_table, shift>;
			static constexpr auto equality    = regular<equality_table,    comparision>;
			static constexpr auto spaceship   = regular<spaceship_table,   equality>;
			static constexpr auto logical_or  = logical<log_or_table,      spaceship>;
			static constexpr auto logical_and = logical<log_and_table,     logical_or>;
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

