#include "parse.hxx"

namespace ltn::c {
	ast::expr_ptr parse_null(const Token &, Tokens &);
	ast::expr_ptr parse_true(const Token &, Tokens &);
	ast::expr_ptr parse_false(const Token &, Tokens &);

	ast::expr_ptr parse_character(const Token &, Tokens &);

	ast::expr_ptr parse_integer_dec(const Token &, Tokens &);
	ast::expr_ptr parse_integer_hex(const Token &, Tokens &);
	ast::expr_ptr parse_integer_bin(const Token &, Tokens &);

	ast::expr_ptr parse_floating(const Token &, Tokens &);
	
	ast::expr_ptr parse_string(const Token &, Tokens &);
	
	ast::expr_ptr parse_iife(const Token &, Tokens &);
	ast::expr_ptr parse_fx_pointer(const Token &, Tokens &);
	ast::expr_ptr parse_custom(const Token &, Tokens &);
	ast::expr_ptr parse_type(const Token &, Tokens &);

	ast::expr_ptr parse_identifier_relative(const Token &, Tokens &);
	ast::expr_ptr parse_identifier_absolute(const Token &, Tokens &);

	ast::expr_ptr parse_neg(const Token & begin, Tokens & tokens);
	ast::expr_ptr parse_not(const Token & begin, Tokens & tokens);
	ast::expr_ptr parse_nul(const Token & begin, Tokens & tokens);
	ast::expr_ptr parse_bitnot(const Token & begin, Tokens & tokens);


	ast::expr_ptr parse_index(const Token &, Tokens &, ast::expr_ptr);
	ast::expr_ptr parse_member(const Token &, Tokens &, ast::expr_ptr);
	ast::expr_ptr parse_member_call(const Token &, Tokens &, ast::expr_ptr);
	ast::expr_ptr parse_call(const Token &, Tokens &, ast::expr_ptr l);


	namespace {
		using TT = Token::Type;
		const std::map<TT, ExprRule> expr_rules {
			{ TT::MINUS, ExprRule { parse_neg, std::nullopt, Precedence::PREFIX_UNARY }},
			{ TT::XMARK, ExprRule { parse_not, std::nullopt, Precedence::PREFIX_UNARY }},
			{ TT::QMARK, ExprRule { parse_nul, std::nullopt, Precedence::PREFIX_UNARY }},

			{ TT::TILDE, ExprRule {
				.prefix = parse_bitnot,
				.infix = std::nullopt,
				.precedence = Precedence::PREFIX_UNARY,
			}},

			{ TT::NVLL, ExprRule {
				.prefix = parse_null,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::FALSE, ExprRule {
				.prefix = parse_false,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::TRUE, ExprRule {
				.prefix = parse_true,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::CHAR, ExprRule {
				.prefix = parse_character,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::INTEGER, ExprRule {
				.prefix = parse_integer_dec,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},
			
			{ TT::INTEGER_BIN, ExprRule {
				.prefix = parse_integer_bin,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::INTEGER_HEX, ExprRule {
				.prefix = parse_integer_hex,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::FLOAT, ExprRule {
				.prefix = parse_floating,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::STRING, ExprRule {
				.prefix = parse_string,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::BRACKET_L, ExprRule {
				.prefix = parse_array,
				.infix = parse_index,
				.precedence = Precedence::POSTFIX_UNARY,
			}},

			{ TT::PAREN_L, ExprRule {
				.prefix = parse_parenthesized,
				.infix = parse_call,
				.precedence = Precedence::POSTFIX_UNARY,
			}},

			{ TT::RARROW, ExprRule {
				.prefix = std::nullopt,
				.infix = parse_member_call,
				.precedence = Precedence::POSTFIX_UNARY,
			}},

			{ TT::DOT, ExprRule {
				.prefix = std::nullopt,
				.infix = parse_member,
				.precedence = Precedence::POSTFIX_UNARY,
			}},

			{ TT::LAMBDA, ExprRule {
				.prefix = parse_lambda,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::IIFE, ExprRule {
				.prefix = parse_iife,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::REFLECT, ExprRule {
				.prefix = parse_reflect,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::AT, ExprRule {
				.prefix = parse_custom,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::CHOOSE, ExprRule {
				.prefix = parse_expr_switch,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::SMALLER, ExprRule {
				.prefix = parse_type,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::AMPERSAND, ExprRule {
				.prefix = parse_fx_pointer,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::INDENTIFIER, ExprRule {
				.prefix = parse_identifier_relative,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},

			{ TT::COLONx2, ExprRule {
				.prefix = parse_identifier_absolute,
				.infix = std::nullopt,
				.precedence = Precedence::NONE,
			}},
		};
	}

	
	
	stx::optref<const ExprRule> get_expr_rule(Token::Type tt) {
		if(expr_rules.contains(tt)) {
			return expr_rules.at(tt);
		}
		return stx::nullref;
	}
}