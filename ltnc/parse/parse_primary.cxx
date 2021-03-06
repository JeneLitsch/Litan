#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include <bitset>
namespace ltn::c {
	namespace {
		using TT = Token::Type;



		CompilerError expected(std::string token, const Tokens & tokens) {
			return {"Expected " + token, location(tokens)};
		}



		template<auto top_presedence>
		ast::expr_ptr parse_paren_base(Tokens & tokens) {
			if(match(TT::PAREN_L, tokens)) {
				auto expr = top_presedence(tokens);
				if(!match(TT::PAREN_R, tokens)) {
					throw expected("(", tokens);
				}
				return expr;
			}
			return nullptr;
		}

		constexpr auto parse_paren        = parse_paren_base<parse_expression>;
		constexpr auto parse_static_paren = parse_paren_base<parse_static_expression>;



		template<class TempType, TT tt, auto base>
		ast::litr_ptr parse_integer(Tokens & tokens) {
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



		ast::litr_ptr parse_character(Tokens & tokens) {
			if(auto t = match(TT::CHAR, tokens)) {
				const char chr = t->str.front();
				return std::make_unique<ast::Char>(chr, location(tokens)); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_null(Tokens & tokens) {
			if(auto t = match(TT::NVLL, tokens)) {
				return std::make_unique<ast::Null>(location(tokens)); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_floating(Tokens & tokens) {
			if(auto token = match(TT::FLOAT, tokens)) {
				std::istringstream iss{token->str};
				stx::float64_t value;
				iss >> value;
				return std::make_unique<ast::Float>(value, location(tokens)); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_boolean(Tokens & tokens) {
			if(auto token = match(TT::TRUE, tokens)) {
				return std::make_unique<ast::Bool>(true, location(tokens)); 
			}
			if(auto token = match(TT::FALSE, tokens)) {
				return std::make_unique<ast::Bool>(false, location(tokens)); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_empty_array(Tokens & tokens) {
			return std::make_unique<ast::Array>(location(tokens));
		}



		template<auto element>
		ast::litr_ptr parse_filled_array(Tokens & tokens) {
			auto array = std::make_unique<ast::Array>(location(tokens));
			while(true) {
				if(match(TT::___EOF___, tokens)) {
					throw expected("]", tokens);
				}
				array->elements.push_back(element(tokens));
				// Last comma is optional
				// A missing last comma is not an error if ] follows
				const bool comma = !!match(TT::COMMA, tokens);
				if(match(TT::BRACKET_R, tokens)) {
					return array;
				}
				// Only throw on missings commas in case of an unclosed array
				if(!comma) {
					throw expected(",", tokens);
				}
			}
		}


		template<auto element>
		ast::litr_ptr parse_array_base(Tokens & tokens) {
			if(match(TT::BRACKET_L, tokens)) {
				if(match(TT::BRACKET_R, tokens)) {
					return parse_empty_array(tokens);
				}
				else {
					return parse_filled_array<element>(tokens);
				}
			}
			return nullptr;
		}
		constexpr auto parse_array = parse_array_base<parse_expression>;
		constexpr auto parse_static_array = parse_array_base<parse_static_expression>;



		ast::litr_ptr parse_string(Tokens & tokens) {
			if(auto token = match(TT::STRING, tokens)) {
				return std::make_unique<ast::String>(
					token->str,
					location(tokens)); 
			}
			return nullptr;
		}



		auto parse_parameters(Tokens & tokens, auto fxParam) {
			if(match(TT::PAREN_R, tokens)) {
				 return;
			}
			while(true) {
				fxParam();
				if(match(TT::PAREN_R, tokens)) {
					return;
				}
				if(!match(TT::COMMA, tokens)) {
					throw expected(",", tokens);
				}
			}
		}



		auto parse_parameters(Tokens & tokens) {
			std::vector<std::unique_ptr<ast::Expression>> parameters;
			parse_parameters(tokens, [&] {
				parameters.push_back(parse_expression(tokens));
			});
			return parameters;
		}



		auto parse_placeholder(Tokens & tokens) {
			std::size_t parameters = 0;
			parse_parameters(tokens, [&] {
				if (!match(TT::UNDERSCORE, tokens)) {
					throw expected("placeholder _", tokens);
				}
				parameters++;
			});
			return parameters;
		}



		std::pair<std::string, ast::Namespace> parse_symbol(Tokens & tokens) {
			ast::Namespace namespaze;
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
			throw expected("indentifier", tokens);
		}



		ast::expr_ptr parse_call(
			const auto & name,
			const auto & namespaze,
			Tokens & tokens) {
			auto parameters = parse_parameters(tokens);
			return std::make_unique<ast::Call>(
				name,
				namespaze,
				std::move(parameters),
				location(tokens));
		}



		auto parse_var(const auto & name, const auto & tokens) {
			return std::make_unique<ast::Var>(name, location(tokens));
		}



		ast::expr_ptr parse_global_value(
			const auto & name,
			const auto & namespaze,
			Tokens & tokens) {
			return std::make_unique<ast::GlobalValue>(
				name,
				namespaze,
				location(tokens));
		}

		

		ast::expr_ptr parse_identifier(Tokens & tokens) {
			const auto [name, namespaze] = parse_symbol(tokens);
			if(match(TT::PAREN_L, tokens)) {
				return parse_call(name, namespaze, tokens);
			}
			if(namespaze.empty()) {
				return parse_var(name, tokens);
			}
			return parse_global_value(name, namespaze, tokens);
		}



		ast::expr_ptr parse_static_identifier(Tokens & tokens) {
			const auto [name, namespaze] = parse_symbol(tokens);
			if(match(TT::PAREN_L, tokens)) {
				throw CompilerError{"Function calls are not allowed in static expression", location(tokens)};
			}
			return parse_global_value(name, namespaze, tokens);
		}



		ast::expr_ptr parse_fx_pointer(Tokens & tokens) {
			if(match(TT::AMPERSAND, tokens)) {
				const auto [name, namespaze] = parse_symbol(tokens);
				if(match(TT::PAREN_L, tokens)) {
					const auto placeholders = parse_placeholder(tokens);
					return std::make_unique<ast::FxPointer>(
						name, namespaze, placeholders, location(tokens));
				}
				throw expected("(", tokens);
			}
			return nullptr; 
		}



		ast::expr_ptr parse_static_iife(Tokens & tokens) {
			if(match(TT::IIFE, tokens)) {
				throw CompilerError{"IIFEs are not allowed in static expression", location(tokens)};
			}
			else return nullptr;
		}



		ast::expr_ptr parse_static_invokation(Tokens & tokens) {
			if(match(TT::RARROW, tokens)) {
				throw CompilerError{"Cannot invoke function in static expression", location(tokens)};
			}
			else return nullptr;
		}



		ast::expr_ptr parse_iife(Tokens & tokens) {
			if(match(TT::IIFE, tokens)) {
				auto body = parse_block(tokens);
				return std::make_unique<ast::Iife>(
					location(tokens),
					std::move(body));
			}
			else return nullptr;
		}
	}



	ast::litr_ptr parse_integral(Tokens & tokens) {
		if(auto expr = parse_integer_dec(tokens)) return expr;
		if(auto expr = parse_integer_bin(tokens)) return expr;
		if(auto expr = parse_integer_hex(tokens)) return expr;
		else return nullptr;
	}



	// parses primary expression
	ast::expr_ptr parse_static_primary(Tokens & tokens) {
		static constexpr auto parse_static_integral = parse_integral;
		static constexpr auto parse_static_character = parse_character;
		static constexpr auto parse_static_floating = parse_floating;
		static constexpr auto parse_static_boolean = parse_boolean;
		static constexpr auto parse_static_null = parse_null;
		static constexpr auto parse_static_string = parse_string;
		static constexpr auto parse_static_fx_pointer = parse_fx_pointer;
		static constexpr auto parse_static_lambda = parse_lambda;
		static constexpr auto parse_static_expr_switch = parse_expr_switch;
		
		if(auto expr = parse_static_integral(tokens)) return expr;
		if(auto expr = parse_static_character(tokens)) return expr;
		if(auto expr = parse_static_floating(tokens)) return expr;
		if(auto expr = parse_static_boolean(tokens)) return expr;
		if(auto expr = parse_static_null(tokens)) return expr;
		if(auto expr = parse_static_string(tokens)) return expr;
		if(auto expr = parse_static_array(tokens)) return expr;
		if(auto expr = parse_static_paren(tokens)) return expr;
		if(auto expr = parse_static_fx_pointer(tokens)) return expr;
		if(auto expr = parse_static_lambda(tokens)) return expr;
		if(auto expr = parse_static_iife(tokens)) return expr;
		if(auto expr = parse_static_invokation(tokens)) return expr;
		if(auto expr = parse_static_expr_switch(tokens)) return expr;
		return parse_static_identifier(tokens);
	}



	// parses primary expression
	ast::expr_ptr parse_primary(Tokens & tokens) {
		if(auto expr = parse_integral(tokens)) return expr;
		if(auto expr = parse_character(tokens)) return expr;
		if(auto expr = parse_floating(tokens)) return expr;
		if(auto expr = parse_boolean(tokens)) return expr;
		if(auto expr = parse_null(tokens)) return expr;
		if(auto expr = parse_string(tokens)) return expr;
		if(auto expr = parse_array(tokens)) return expr;
		if(auto expr = parse_paren(tokens)) {
			if(match(TT::PAREN_L, tokens)) {
				auto params = parse_parameters(tokens);
				return std::make_unique<ast::Invokation>(
					std::move(std::move(expr)),
					std::move(params),
					location(tokens)
				);
			}
			return expr; 

		}
		if(auto expr = parse_fx_pointer(tokens)) return expr;
		if(auto expr = parse_lambda(tokens)) return expr;
		if(auto expr = parse_iife(tokens)) return expr;
		if(auto expr = parse_expr_switch(tokens)) return expr;
		return parse_identifier(tokens);
	}
}

