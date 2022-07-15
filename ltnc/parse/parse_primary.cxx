#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include <bitset>
namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;



		CompilerError expected(std::string token, const lex::Lexer & lexer) {
			return {"Expected " + token, lexer.location()};
		}



		template<auto top_presedence>
		ast::expr_ptr parse_paren_base(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) {
				auto expr = top_presedence(lexer);
				if(!lexer.match(TT::PAREN_R)) {
					throw expected("(", lexer);
				}
				return expr;
			}
			return nullptr;
		}

		constexpr auto parse_paren        = parse_paren_base<parse_expression>;
		constexpr auto parse_static_paren = parse_paren_base<parse_static_expression>;



		template<class TempType, TT tt, auto base>
		ast::litr_ptr parse_integer(lex::Lexer & lexer) {
			if(auto token = lexer.match(tt)) {
				std::stringstream iss{token->str};
				TempType value;
				iss >> base >> value;
				return std::make_unique<ast::Integer>(value, lexer.location()); 
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



		ast::litr_ptr parse_character(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::CHAR)) {
				const char chr = t->str.front();
				return std::make_unique<ast::Char>(chr, lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_null(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::NVLL)) {
				return std::make_unique<ast::Null>(lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_floating(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::FLOAT)) {
				std::istringstream iss{token->str};
				stx::float64_t value;
				iss >> value;
				return std::make_unique<ast::Float>(value, lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_boolean(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::TRUE)) {
				return std::make_unique<ast::Bool>(true, lexer.location()); 
			}
			if(auto token = lexer.match(TT::FALSE)) {
				return std::make_unique<ast::Bool>(false, lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr parse_empty_array(lex::Lexer & lexer) {
			return std::make_unique<ast::Array>(lexer.location());
		}



		template<auto element>
		ast::litr_ptr parse_filled_array(lex::Lexer & lexer) {
			auto array = std::make_unique<ast::Array>(lexer.location());
			while(true) {
				if(lexer.match(TT::___EOF___)) {
					throw expected("]", lexer);
				}
				array->elements.push_back(element(lexer));
				// Last comma is optional
				// A missing last comma is not an error if ] follows
				const bool comma = !!lexer.match(TT::COMMA);
				if(lexer.match(TT::BRACKET_R)) {
					return array;
				}
				// Only throw on missings commas in case of an unclosed array
				if(!comma) {
					throw expected(",", lexer);
				}
			}
		}


		template<auto element>
		ast::litr_ptr parse_array_base(lex::Lexer & lexer) {
			if(lexer.match(TT::BRACKET_L)) {
				if(lexer.match(TT::BRACKET_R)) {
					return parse_empty_array(lexer);
				}
				else {
					return parse_filled_array<element>(lexer);
				}
			}
			return nullptr;
		}
		constexpr auto parse_array = parse_array_base<parse_expression>;
		constexpr auto parse_static_array = parse_array_base<parse_static_expression>;



		ast::litr_ptr parse_string(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::STRING)) {
				return std::make_unique<ast::String>(
					token->str,
					lexer.location()); 
			}
			return nullptr;
		}



		auto parse_parameters(lex::Lexer & lexer, auto fxParam) {
			if(lexer.match(TT::PAREN_R)) {
				 return;
			}
			while(true) {
				fxParam();
				if(lexer.match(TT::PAREN_R)) {
					return;
				}
				if(!lexer.match(TT::COMMA)) {
					throw expected(",", lexer);
				}
			}
		}



		auto parse_parameters(lex::Lexer & lexer) {
			std::vector<std::unique_ptr<ast::Expression>> parameters;
			parse_parameters(lexer, [&] {
				parameters.push_back(parse_expression(lexer));
			});
			return parameters;
		}



		auto parse_placeholder(lex::Lexer & lexer) {
			std::size_t parameters = 0;
			parse_parameters(lexer, [&] {
				if (!lexer.match(TT::UNDERSCORE)) {
					throw expected("placeholder _", lexer);
				}
				parameters++;
			});
			return parameters;
		}



		std::pair<std::string, ast::Namespace> parse_symbol(lex::Lexer & lexer) {
			ast::Namespace namespaze;
			if(lexer.match(TT::COLONx2)) {
				namespaze.set_absolute();
			}
			if(const auto & identifier = lexer.match(TT::INDENTIFIER)) {
				namespaze.push_back(identifier->str);
				std::string name = identifier->str;
				while(lexer.match(TT::COLONx2)) {
					if(auto i = lexer.match(TT::INDENTIFIER)) {
						namespaze.push_back(i->str);
						name = i->str;
					}
				}
				namespaze.pop_back();
				return {name, namespaze};
			}
			throw expected("indentifier", lexer);
		}



		ast::expr_ptr parse_call(
			const auto & name,
			const auto & namespaze,
			lex::Lexer & lexer) {
			auto parameters = parse_parameters(lexer);
			return std::make_unique<ast::Call>(
				name,
				namespaze,
				std::move(parameters),
				lexer.location());
		}



		auto parse_var(const auto & name, const auto & lexer) {
			return std::make_unique<ast::Var>(name, lexer.location());
		}



		ast::expr_ptr parse_global_value(
			const auto & name,
			const auto & namespaze,
			lex::Lexer & lexer) {
			return std::make_unique<ast::GlobalValue>(
				name,
				namespaze,
				lexer.location());
		}

		

		ast::expr_ptr parse_identifier(lex::Lexer & lexer) {
			const auto [name, namespaze] = parse_symbol(lexer);
			if(lexer.match(TT::PAREN_L)) {
				return parse_call(name, namespaze, lexer);
			}
			if(namespaze.empty()) {
				return parse_var(name, lexer);
			}
			return parse_global_value(name, namespaze, lexer);
		}



		ast::expr_ptr parse_static_identifier(lex::Lexer & lexer) {
			const auto [name, namespaze] = parse_symbol(lexer);
			if(lexer.match(TT::PAREN_L)) {
				throw CompilerError{"Function calls are not allowed in static expression", lexer.location()};
			}
			return parse_global_value(name, namespaze, lexer);
		}



		ast::expr_ptr parse_fx_pointer(lex::Lexer & lexer) {
			if(lexer.match(TT::AMPERSAND)) {
				const auto [name, namespaze] = parse_symbol(lexer);
				if(lexer.match(TT::PAREN_L)) {
					const auto placeholders = parse_placeholder(lexer);
					return std::make_unique<ast::FxPointer>(
						name, namespaze, placeholders, lexer.location());
				}
				throw expected("(", lexer);
			}
			return nullptr; 
		}



		ast::expr_ptr parse_static_iife(lex::Lexer & lexer) {
			if(lexer.match(TT::IIFE)) {
				throw CompilerError{"IIFEs are not allowed in static expression", lexer.location()};
			}
			else return nullptr;
		}



		ast::expr_ptr parse_static_invokation(lex::Lexer & lexer) {
			if(lexer.match(TT::RARROW)) {
				throw CompilerError{"Cannot invoke function in static expression", lexer.location()};
			}
			else return nullptr;
		}



		ast::expr_ptr parse_iife(lex::Lexer & lexer) {
			if(lexer.match(TT::IIFE)) {
				auto body = parse_block(lexer);
				return std::make_unique<ast::Iife>(
					lexer.location(),
					std::move(body));
			}
			else return nullptr;
		}
	}



	ast::litr_ptr parse_integral(lex::Lexer & lexer) {
		if(auto expr = parse_integer_dec(lexer)) return expr;
		if(auto expr = parse_integer_bin(lexer)) return expr;
		if(auto expr = parse_integer_hex(lexer)) return expr;
		else return nullptr;
	}



	// parses primary expression
	ast::expr_ptr parse_static_primary(lex::Lexer & lexer) {
		static constexpr auto parse_static_integral = parse_integral;
		static constexpr auto parse_static_character = parse_character;
		static constexpr auto parse_static_floating = parse_floating;
		static constexpr auto parse_static_boolean = parse_boolean;
		static constexpr auto parse_static_null = parse_null;
		static constexpr auto parse_static_string = parse_string;
		static constexpr auto parse_static_fx_pointer = parse_fx_pointer;
		static constexpr auto parse_static_lambda = parse_lambda;
		static constexpr auto parse_static_expr_switch = parse_expr_switch;
		
		if(auto expr = parse_static_integral(lexer)) return expr;
		if(auto expr = parse_static_character(lexer)) return expr;
		if(auto expr = parse_static_floating(lexer)) return expr;
		if(auto expr = parse_static_boolean(lexer)) return expr;
		if(auto expr = parse_static_null(lexer)) return expr;
		if(auto expr = parse_static_string(lexer)) return expr;
		if(auto expr = parse_static_array(lexer)) return expr;
		if(auto expr = parse_static_paren(lexer)) return expr;
		if(auto expr = parse_static_fx_pointer(lexer)) return expr;
		if(auto expr = parse_static_lambda(lexer)) return expr;
		if(auto expr = parse_static_iife(lexer)) return expr;
		if(auto expr = parse_static_invokation(lexer)) return expr;
		if(auto expr = parse_static_expr_switch(lexer)) return expr;
		return parse_static_identifier(lexer);
	}



	// parses primary expression
	ast::expr_ptr parse_primary(lex::Lexer & lexer) {
		if(auto expr = parse_integral(lexer)) return expr;
		if(auto expr = parse_character(lexer)) return expr;
		if(auto expr = parse_floating(lexer)) return expr;
		if(auto expr = parse_boolean(lexer)) return expr;
		if(auto expr = parse_null(lexer)) return expr;
		if(auto expr = parse_string(lexer)) return expr;
		if(auto expr = parse_array(lexer)) return expr;
		if(auto expr = parse_paren(lexer)) {
			if(lexer.match(TT::PAREN_L)) {
				auto params = parse_parameters(lexer);
				return std::make_unique<ast::Invokation>(
					std::move(std::move(expr)),
					std::move(params),
					lexer.location()
				);
			}
			return expr; 

		}
		if(auto expr = parse_fx_pointer(lexer)) return expr;
		if(auto expr = parse_lambda(lexer)) return expr;
		if(auto expr = parse_iife(lexer)) return expr;
		if(auto expr = parse_expr_switch(lexer)) return expr;
		return parse_identifier(lexer);
	}
}

