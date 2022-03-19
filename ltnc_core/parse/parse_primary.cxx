#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"
#include <sstream>
#include <bitset>
#include "ltn/reading.hxx"
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;



		CompilerError expected(std::string token, const lex::Lexer & lexer) {
			return {"Expected " + token, lexer.location()};
		}



		template<auto top_presedence>
		ast::expr_ptr paren_base(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) {
				auto expr = top_presedence(lexer);
				if(!lexer.match(TT::PAREN_R)) {
					throw expected("(", lexer);
				}
				return expr;
			}
			return nullptr;
		}

		constexpr auto paren = paren_base<expression>;
		constexpr auto static_paren = paren_base<static_expression>;



		template<class TempType, TT tt, auto base>
		ast::litr_ptr integer(lex::Lexer & lexer) {
			if(auto token = lexer.match(tt)) {
				std::stringstream iss{token->str};
				TempType value;
				iss >> base >> value;
				return std::make_unique<ast::Integer>(value, lexer.location()); 
			}
			return nullptr;
		}
		constexpr auto integer_dec = integer<
			std::int64_t,
			TT::INTEGER,
			std::dec>;
		
		constexpr auto integer_hex = integer<
			std::int64_t,
			TT::INTEGER_HEX,
			std::hex>;
		
		constexpr auto integer_bin = integer<
			std::bitset<64>,
			TT::INTEGER_BIN,
			std::dec>;



		ast::litr_ptr character(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::CHAR)) {
				const char chr = t->str.front();
				return std::make_unique<ast::Char>(chr, lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr null(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::NVLL)) {
				return std::make_unique<ast::Null>(lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr floating(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::FLOAT)) {
				std::istringstream iss{token->str};
				stx::float64_t value;
				iss >> value;
				return std::make_unique<ast::Float>(value, lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr boolean(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::TRUE)) {
				return std::make_unique<ast::Bool>(true, lexer.location()); 
			}
			if(auto token = lexer.match(TT::FALSE)) {
				return std::make_unique<ast::Bool>(false, lexer.location()); 
			}
			return nullptr;
		}



		ast::litr_ptr empty_array(lex::Lexer & lexer) {
			return std::make_unique<ast::Array>(lexer.location());
		}



		template<auto element>
		ast::litr_ptr filled_array(lex::Lexer & lexer) {
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
		ast::litr_ptr array_base(lex::Lexer & lexer) {
			if(lexer.match(TT::BRACKET_L)) {
				if(lexer.match(TT::BRACKET_R)) {
					return empty_array(lexer);
				}
				else {
					return filled_array<element>(lexer);
				}
			}
			return nullptr;
		}
		constexpr auto array = array_base<parse::expression>;
		constexpr auto static_array = array_base<parse::static_expression>;



		ast::litr_ptr string(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::STRING)) {
				return std::make_unique<ast::String>(
					token->str,
					lexer.location()); 
			}
			return nullptr;
		}



		auto parameters(lex::Lexer & lexer, auto fxParam) {
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



		auto parameters(lex::Lexer & lexer) {
			std::vector<std::unique_ptr<ast::Expression>> parameters;
			parse::parameters(lexer, [&] {
				parameters.push_back(expression(lexer));
			});
			return parameters;
		}



		auto placeholder(lex::Lexer & lexer) {
			std::size_t parameters = 0;
			parse::parameters(lexer, [&] {
				if (!lexer.match(TT::UNDERSCORE)) {
					throw expected("placeholder _", lexer);
				}
				parameters++;
			});
			return parameters;
		}



		std::pair<std::string, ast::Namespace> symbol(lex::Lexer & lexer) {
			ast::Namespace namespaze;
			if(lexer.match(TT::COLONx2)) {
				namespaze.push_back("::");
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



		ast::expr_ptr call(
			const auto & name,
			const auto & namespaze,
			lex::Lexer & lexer) {
			auto parameters = parse::parameters(lexer);
			return std::make_unique<ast::Call>(
				name,
				namespaze,
				std::move(parameters),
				lexer.location());
		}



		auto var(const auto & name, const auto & lexer) {
			return std::make_unique<ast::Var>(name, lexer.location());
		}



		ast::expr_ptr global_value(
			const auto & name,
			const auto & namespaze,
			lex::Lexer & lexer) {
			return std::make_unique<ast::GlobalValue>(
				name,
				namespaze,
				lexer.location());
		}

		

		ast::expr_ptr identifier(lex::Lexer & lexer) {
			const auto [name, namespaze] = symbol(lexer);
			if(lexer.match(TT::PAREN_L)) {
				return parse::call(name, namespaze, lexer);
			}
			if(namespaze.empty()) {
				return parse::var(name, lexer);
			}
			return global_value(name, namespaze, lexer);
		}



		ast::expr_ptr static_identifier(lex::Lexer & lexer) {
			const auto [name, namespaze] = symbol(lexer);
			if(lexer.match(TT::PAREN_L)) {
				throw CompilerError{"Function calls are not allowed in static expression", lexer.location()};
			}
			return global_value(name, namespaze, lexer);
		}



		ast::expr_ptr fx_pointer(lex::Lexer & lexer) {
			if(lexer.match(TT::AMPERSAND)) {
				const auto [name, namespaze] = symbol(lexer);
				if(lexer.match(TT::PAREN_L)) {
					const auto placeholders = parse::placeholder(lexer);
					return std::make_unique<ast::FxPointer>(
						name, namespaze, placeholders, lexer.location());
				}
				throw expected("(", lexer);
			}
			return nullptr; 
		}



		ast::expr_ptr static_iife(lex::Lexer & lexer) {
			if(lexer.match(TT::IIFE)) {
				throw CompilerError{"IIFEs are not allowed in static expression", lexer.location()};
			}
			else return nullptr;
		}



		ast::expr_ptr iife(lex::Lexer & lexer) {
			if(lexer.match(TT::IIFE)) {
				auto body = parse::block(lexer);
				return std::make_unique<ast::Iife>(
					lexer.location(),
					std::move(body));
			}
			else return nullptr;
		}
	}



	ast::litr_ptr integral(lex::Lexer & lexer) {
		if(auto expr = integer_dec(lexer)) return expr;
		if(auto expr = integer_bin(lexer)) return expr;
		if(auto expr = integer_hex(lexer)) return expr;
		else return nullptr;
	}



	// parses primary expression
	ast::expr_ptr static_primary(lex::Lexer & lexer) {
		static constexpr auto static_integral = integral;
		static constexpr auto static_character = character;
		static constexpr auto static_floating = floating;
		static constexpr auto static_boolean = boolean;
		static constexpr auto static_null = null;
		static constexpr auto static_string = string;
		static constexpr auto static_fx_pointer = fx_pointer;
		static constexpr auto static_lambda = lambda;
		
		if(auto expr = static_integral(lexer)) return expr;
		if(auto expr = static_character(lexer)) return expr;
		if(auto expr = static_floating(lexer)) return expr;
		if(auto expr = static_boolean(lexer)) return expr;
		if(auto expr = static_null(lexer)) return expr;
		if(auto expr = static_string(lexer)) return expr;
		if(auto expr = static_array(lexer)) return expr;
		if(auto expr = static_paren(lexer)) return expr;
		if(auto expr = static_fx_pointer(lexer)) return expr;
		if(auto expr = static_lambda(lexer)) return expr;
		if(auto expr = static_iife(lexer)) return expr;
		return static_identifier(lexer);
	}



	// parses primary expression
	ast::expr_ptr primary(lex::Lexer & lexer) {
		if(auto expr = integral(lexer)) return expr;
		if(auto expr = character(lexer)) return expr;
		if(auto expr = floating(lexer)) return expr;
		if(auto expr = boolean(lexer)) return expr;
		if(auto expr = null(lexer)) return expr;
		if(auto expr = string(lexer)) return expr;
		if(auto expr = array(lexer)) return expr;
		if(auto expr = paren(lexer)) return expr;
		if(auto expr = fx_pointer(lexer)) return expr;
		if(auto expr = lambda(lexer)) return expr;
		if(auto expr = iife(lexer)) return expr;
		return identifier(lexer);
	}
}

