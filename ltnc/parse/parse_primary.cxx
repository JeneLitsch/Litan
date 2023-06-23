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
		ast::expr_ptr parse_integer(const Token & begin, Tokens & tokens) {
			std::stringstream iss{begin.str};
			TempType value;
			iss >> base >> value;
			return std::make_unique<ast::Integer>(value, begin.location); 
		}



		ast::expr_ptr parse_character(const Token & begin, Tokens & tokens) {
			const auto chr = static_cast<std::uint8_t>(begin.str.front());
			return std::make_unique<ast::Char>(chr, location(tokens)); 
		}



		ast::expr_ptr parse_null(const Token & begin, Tokens & tokens) {
			return std::make_unique<ast::Null>(location(tokens)); 
		}



		ast::expr_ptr parse_floating(const Token & begin, Tokens & tokens) {
			std::istringstream iss{begin.str};
			stx::float64_t value;
			iss >> value;
			return std::make_unique<ast::Float>(value, location(tokens)); 
		}



		ast::expr_ptr parse_false(const Token & begin, Tokens & tokens) {
			return std::make_unique<ast::Bool>(false, location(tokens)); 
		}



		ast::expr_ptr parse_true(const Token & begin, Tokens & tokens) {
			return std::make_unique<ast::Bool>(true, location(tokens)); 
		}



		ast::expr_ptr parse_string(const Token & begin, Tokens & tokens) {
			return std::make_unique<ast::String>(begin.str, location(tokens)); 
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



		template<auto parse_symbol>
		ast::expr_ptr parse_identifier(const Token & begin, Tokens & tokens) {
			const auto [name, namespaze] = parse_symbol(begin, tokens);
			return std::make_unique<ast::Var>(name, namespaze, location(tokens));
		}



		ast::expr_ptr parse_fx_pointer(const Token & begin, Tokens & tokens) {
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



		ast::expr_ptr parse_iife(const Token & begin, Tokens & tokens) {
			auto body = parse_block(tokens);
			return std::make_unique<ast::Iife>(begin.location, std::move(body));
		}



		ast::expr_ptr parse_custom(const Token & begin,Tokens & tokens) {
			const auto & loc = begin.location;
			auto type = match(TT::INDENTIFIER, tokens);
			if(!type) throw expected("Expected custom type", loc);
			if(!match(TT::PAREN_L, tokens)) throw expected("(", loc);
			auto value = match(TT::STRING, tokens);
			if(!value) throw expected("Expected string", loc);
			if(!match(TT::PAREN_R, tokens)) throw expected(")", loc);

			return std::make_unique<ast::CustomLiteral>(type->str, value->str, loc);
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



	std::pair<std::string, Namespace> parse_symbol_relative(const Token & begin, Tokens & tokens) {
		Namespace namespaze;
		namespaze.push_back(begin.str);
		std::string name = begin.str;
		while(match(TT::COLONx2, tokens)) {
			if(auto i = match(TT::INDENTIFIER, tokens)) {
				namespaze.push_back(i->str);
				name = i->str;
			}
		}
		namespaze.pop_back();
		return {name, namespaze};
	}



	std::pair<std::string, Namespace> parse_symbol_absolute(const Token & begin, Tokens & tokens) {
		auto [name, namespaze] = parse_symbol(tokens);
		namespaze.set_absolute();
		return {name, namespaze};
	}



	std::pair<std::string, Namespace> parse_symbol(Tokens & tokens) {
		Namespace namespaze;
		if(auto colon2x = match(TT::COLONx2, tokens)) {
			return parse_symbol_absolute(*colon2x, tokens);
		}
		else if(auto identifier = match(TT::INDENTIFIER, tokens)) {
			return parse_symbol_relative(*identifier, tokens);
		}
		else {
			throw expected("indentifier", location(tokens));
		}
	}



	const std::map<TT, ExprRule> expr_rules {

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
			.prefix = parse_integer<std::int64_t, TT::INTEGER, std::dec>,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},
		
		{ TT::INTEGER_BIN, ExprRule {
			.prefix = parse_integer<std::bitset<64>, TT::INTEGER_BIN, std::dec>,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::INTEGER_HEX, ExprRule {
			.prefix = parse_integer<std::int64_t, TT::INTEGER_HEX, std::hex>,
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
			.prefix = parse_identifier<parse_symbol_relative>,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},

		{ TT::COLONx2, ExprRule {
			.prefix = parse_identifier<parse_symbol_absolute>,
			.infix = std::nullopt,
			.precedence = Precedence::NONE,
		}},
	};



	// parses primary expr
	ast::expr_ptr parse_primary(Tokens & tokens) {
		auto begin = tokens.front();
		tokens.pop();
		auto tt = begin.type;
		if(expr_rules.contains(tt)) {
			return (*expr_rules.at(tt).prefix)(begin, tokens);
		}

		throw CompilerError { "Expected expression", begin.location };

	}
}

