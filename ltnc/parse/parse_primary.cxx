#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "stdxx/iife.hxx"
#include <sstream>
#include <bitset>
namespace ltn::c {
	namespace {
		using TT = Token::Type;



		CompilerError expected(std::string token, const SourceLocation & location) {
			return {"Expected " + token, location};
		}



		template<class TempType, TT tt, auto base>
		ast::expr_ptr parse_integer(Tokens & tokens) {
			if(auto token = match(tt, tokens)) {
				std::stringstream iss{token->str};
				TempType value;
				iss >> base >> value;
				return std::make_unique<ast::Integer>(value, location(tokens)); 
			}
			return nullptr;
		}
		constexpr auto parse_integer_dec = parse_integer<
			std::int64_t,
			TT::INTEGER,
			std::dec>;
		constexpr auto parse_integer_hex = parse_integer<
			std::int64_t,
			TT::INTEGER_HEX,
			std::hex>;
		constexpr auto parse_integer_bin = parse_integer<
			std::bitset<64>,
			TT::INTEGER_BIN,
			std::dec>;



		ast::expr_ptr parse_character(Tokens & tokens) {
			if(auto t = match(TT::CHAR, tokens)) {
				const auto chr = static_cast<std::uint8_t>(t->str.front());
				return std::make_unique<ast::Char>(chr, location(tokens)); 
			}
			return nullptr;
		}



		ast::expr_ptr parse_null(Tokens & tokens) {
			if(auto t = match(TT::NVLL, tokens)) {
				return std::make_unique<ast::Null>(location(tokens)); 
			}
			return nullptr;
		}



		ast::expr_ptr parse_floating(Tokens & tokens) {
			if(auto token = match(TT::FLOAT, tokens)) {
				std::istringstream iss{token->str};
				stx::float64_t value;
				iss >> value;
				return std::make_unique<ast::Float>(value, location(tokens)); 
			}
			return nullptr;
		}



		ast::expr_ptr parse_boolean(Tokens & tokens) {
			if(auto token = match(TT::TRUE, tokens)) {
				return std::make_unique<ast::Bool>(true, location(tokens)); 
			}
			if(auto token = match(TT::FALSE, tokens)) {
				return std::make_unique<ast::Bool>(false, location(tokens)); 
			}
			return nullptr;
		}



		ast::expr_ptr parse_string(Tokens & tokens) {
			if(auto token = match(TT::STRING, tokens)) {
				return std::make_unique<ast::String>(
					token->str,
					location(tokens)); 
			}
			return nullptr;
		}



		auto parse_parameters(
			Tokens & tokens,
			auto fxParam,
			TT close = TT::PAREN_R) {
			
			if(match(close, tokens)) {
				 return;
			}
			while(true) {
				fxParam();
				if(match(close, tokens)) {
					return;
				}
				if(!match(TT::COMMA, tokens)) {
					throw expected(",", location(tokens));
				}
			}
		}



		ast::expr_ptr parse_identifier(Tokens & tokens) {
			const auto [name, namespaze] = parse_symbol(tokens);
			return std::make_unique<ast::Var>(name, namespaze, location(tokens));
		}



		ast::expr_ptr parse_fx_pointer(Tokens & tokens) {
			if(match(TT::AMPERSAND, tokens)) {
				std::string name;
				Namespace namespaze;
				std::tie(name, namespaze) = parse_symbol(tokens);
				if(match(TT::PAREN_L, tokens)) {
					auto [arity, is_variadic] = parse_placeholder(tokens);
					auto fx_ptr = std::make_unique<ast::FxPointer>(
						std::move(name),
						std::move(namespaze),
						arity,
						is_variadic,
						location(tokens));
					return fx_ptr;
				}
				throw expected("(", location(tokens));
			}
			return nullptr; 
		}



		ast::expr_ptr parse_iife(Tokens & tokens) {
			if(match(TT::IIFE, tokens)) {
				auto body = parse_block(tokens);
				return std::make_unique<ast::Iife>(
					location(tokens),
					std::move(body)
				);
			}
			else return nullptr;
		}



		ast::expr_ptr parse_custom(Tokens & tokens) {
			if(auto begin = match(TT::AT, tokens)) {
				const auto & loc = begin->location;
				auto type = match(TT::INDENTIFIER, tokens);
				if(!type) throw expected("Expected custom type", loc);
				if(!match(TT::PAREN_L, tokens)) throw expected("(", loc);
				auto value = match(TT::STRING, tokens);
				if(!value) throw expected("Expected string", loc);
				if(!match(TT::PAREN_R, tokens)) throw expected(")", loc);

				return std::make_unique<ast::CustomLiteral>(type->str, value->str, loc);
			}
			else return nullptr;
		}
	}



	std::tuple<std::uint64_t, bool> parse_placeholder(Tokens & tokens) {
		std::uint64_t placeholders = 0;
		if(match(TT::PAREN_R, tokens)) {
			return {placeholders, false};
		}
		while(true) {
			if(match(TT::UNDERSCORE, tokens)) {
				++placeholders;
			}
			else if(match(TT::ELLIPSIS, tokens)) {
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Variadic placeholder must be last", location(tokens)
				};
				return {placeholders, true};
			}
			if(match(TT::PAREN_R, tokens)) {
				return {placeholders, false};
			}
			if(!match(TT::COMMA, tokens)) {
				throw expected(",", location(tokens));
			}
		}
	}



	std::pair<std::string, Namespace> parse_symbol(Tokens & tokens) {
		Namespace namespaze;
		if(match(TT::COLONx2, tokens)) {
			namespaze.set_absolute();
		}
		if(const auto & identifier = match(TT::INDENTIFIER, tokens)) {
			namespaze.push_back(identifier->str);
			std::string name = identifier->str;
			while(match(TT::COLONx2, tokens)) {
				if(auto i = match(TT::INDENTIFIER, tokens)) {
					namespaze.push_back(i->str);
					name = i->str;
				}
			}
			namespaze.pop_back();
			return {name, namespaze};
		}
		throw expected("indentifier", location(tokens));
	}



	ast::expr_ptr parse_integral(Tokens & tokens) {
		if(auto expr = parse_integer_dec(tokens)) return expr;
		if(auto expr = parse_integer_bin(tokens)) return expr;
		if(auto expr = parse_integer_hex(tokens)) return expr;
		else return nullptr;
	}



	const std::map<TT, ExprRule> expr_rules {

		{ TT::NVLL, ExprRule {
			.prefix = parse_null,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::FALSE, ExprRule {
			.prefix = parse_boolean,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::TRUE, ExprRule {
			.prefix = parse_boolean,
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
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::PAREN_L, ExprRule {
			.prefix = parse_parenthesized,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
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
			.prefix = ParseFx{[] (Tokens & tokens) -> ast::expr_ptr { return parse_type(tokens); }},
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::AMPERSAND, ExprRule {
			.prefix = parse_fx_pointer,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::INDENTIFIER, ExprRule {
			.prefix = parse_identifier,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},
	};



	// parses primary expr
	ast::expr_ptr parse_primary(Tokens & tokens) {
		auto token = tokens.front();
		auto tt = token.type;
		if(expr_rules.contains(tt)) {
			return (*expr_rules.at(tt).prefix)(tokens);
		}

		throw CompilerError { "Expected expression", token.location };

	}
}

