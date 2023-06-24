#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "stdxx/iife.hxx"
#include <sstream>
#include <bitset>
namespace ltn::c {
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



	ast::expr_ptr parse_integer_dec(const Token & begin, Tokens & tokens) {
		return parse_integer<std::int64_t, TT::INTEGER, std::dec>(begin, tokens);
	}



	ast::expr_ptr parse_integer_hex(const Token & begin, Tokens & tokens) {
		return parse_integer<std::int64_t, TT::INTEGER_HEX, std::hex>(begin, tokens);
	}



	ast::expr_ptr parse_integer_bin(const Token & begin, Tokens & tokens) {
		return parse_integer<std::bitset<64>, TT::INTEGER_BIN, std::dec>(begin, tokens);
	}



	ast::expr_ptr parse_identifier_relative(const Token & begin, Tokens & tokens) {
		return parse_identifier<parse_symbol_relative>(begin, tokens);
	}


	ast::expr_ptr parse_identifier_absolute(const Token & begin, Tokens & tokens) {
		return parse_identifier<parse_symbol_absolute>(begin, tokens);
	}
}

