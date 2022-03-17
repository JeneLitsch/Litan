#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include <bitset>
#include "ltn/reading.hxx"
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;



		CompilerError expected(std::string token, const lex::Lexer & lexer) {
			return {"Expected " + token, lexer.location()};
		}



		ast::expr_ptr paren(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) {
				auto expr = expression(lexer);
				if(!lexer.match(TT::PAREN_R)) {
					throw expected("(", lexer);
				}
				return expr;
			}
			return nullptr;
		}



		template<class TempType, TT tt, auto base>
		ast::expr_ptr integer(lex::Lexer & lexer) {
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



		ast::expr_ptr character(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::CHAR)) {
				const char chr = t->str.front();
				return std::make_unique<ast::Char>(chr, lexer.location()); 
			}
			return nullptr;
		}



		ast::expr_ptr null(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::NVLL)) {
				return std::make_unique<ast::Null>(lexer.location()); 
			}
			return nullptr;
		}



		ast::expr_ptr floating(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::FLOAT)) {
				std::istringstream iss{token->str};
				stx::float64_t value;
				iss >> value;
				return std::make_unique<ast::Float>(value, lexer.location()); 
			}
			return nullptr;
		}



		ast::expr_ptr boolean(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::TRUE)) {
				return std::make_unique<ast::Bool>(true, lexer.location()); 
			}
			if(auto token = lexer.match(TT::FALSE)) {
				return std::make_unique<ast::Bool>(false, lexer.location()); 
			}
			return nullptr;
		}



		ast::expr_ptr empty_array(lex::Lexer & lexer) {
			return std::make_unique<ast::Array>(lexer.location());
		}



		ast::expr_ptr filled_array(lex::Lexer & lexer) {
			auto array = std::make_unique<ast::Array>(lexer.location());
			while(true) {
				if(lexer.match(TT::___EOF___)) {
					throw expected("]", lexer);
				}
				array->elements.push_back(expression(lexer));
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



		ast::expr_ptr array(lex::Lexer & lexer) {
			if(lexer.match(TT::BRACKET_L)) {
				if(lexer.match(TT::BRACKET_R)) {
					return empty_array(lexer);
				}
				else {
					return filled_array(lexer);
				}
			}
			return nullptr;
		}



		ast::expr_ptr string(lex::Lexer & lexer) {
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



		ast::expr_ptr enum_value(
			const auto & enum_name,
			const auto & namespaze,
			lex::Lexer & lexer) {
			auto value_name = parse::variable_name(lexer);
			return std::make_unique<ast::EnumValue>(
				enum_name,
				value_name,
				namespaze,
				lexer.location());
		}

		

		ast::expr_ptr identifier(lex::Lexer & lexer) {
			const auto [name, namespaze] = symbol(lexer);
			if(lexer.match(TT::PAREN_L)) {
				return parse::call(name, namespaze, lexer);
			}
			if(lexer.match(TT::AT)) {
				return enum_value(name, namespaze, lexer);
			}
			if(namespaze.empty()) {
				return parse::var(name, lexer);
			}
			throw CompilerError{
				"cannot address variable with namespace in front",
				lexer.location()};
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



	ast::expr_ptr integral(lex::Lexer & lexer) {
		if(auto expr = integer_dec(lexer)) return expr;
		if(auto expr = integer_bin(lexer)) return expr;
		if(auto expr = integer_hex(lexer)) return expr;
		else return nullptr;
	}


	// parses primary expression
	ast::expr_ptr primary(lex::Lexer & lexer) {
		if(auto expr = integral(lexer)) return expr;
		if(auto expr = character(lexer)) return expr;
		if(auto expr = floating(lexer)) return expr;
		if(auto expr = boolean(lexer)) return expr;
		if(auto expr = null(lexer)) return expr;
		if(auto expr = paren(lexer)) return expr;
		if(auto expr = string(lexer)) return expr;
		if(auto expr = array(lexer)) return expr;
		if(auto expr = fx_pointer(lexer)) return expr;
		if(auto expr = lambda(lexer)) return expr;
		if(auto expr = iife(lexer)) return expr;
		return identifier(lexer);
	}
}

