#include "parsing.hxx"
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

		// Literals
		std::unique_ptr<ast::Expression> paren(lex::Lexer & lexer) {
			if(lexer.match(TT::PAREN_L)) {
				auto expr = expression(lexer);
				if(!lexer.match(TT::PAREN_R)) {
					throw expected("(", lexer);
				}
				return expr;
			}
			return nullptr;
		}

		template<class TempType, TT tt>
		std::unique_ptr<ast::Integer> integer(lex::Lexer & lexer) {
			if(auto token = lexer.match(tt)) {
				std::stringstream ss{token->str};
				if constexpr(tt == TT::INTEGER_HEX) {
					ss >> std::hex;
				}
				const TempType value = read<TempType>(ss);
				return std::make_unique<ast::Integer>(value, lexer.location()); 
			}
			return nullptr;
		}

		constexpr auto integerDec = integer<std::int64_t,    TT::INTEGER>;
		constexpr auto integerHex = integer<std::int64_t,    TT::INTEGER_HEX>;
		constexpr auto integerBin = integer<std::bitset<64>, TT::INTEGER_BIN>;



		std::unique_ptr<ast::Char> character(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::CHAR)) {
				return std::make_unique<ast::Char>(t->str[0], lexer.location()); 
			}
			return nullptr;
		}


		std::unique_ptr<ast::Null> null(lex::Lexer & lexer) {
			if(auto t = lexer.match(TT::NVLL)) {
				return std::make_unique<ast::Null>(lexer.location()); 
			}
			return nullptr;
		}


		std::unique_ptr<ast::Float> floating(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::FLOAT)) {
				std::stringstream ss{token->str};
				const double value = read<double>(ss);
				return std::make_unique<ast::Float>(value, lexer.location()); 
			}
			return nullptr;
		}

		std::unique_ptr<ast::Bool> boolean(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::TRUE)) {
				return std::make_unique<ast::Bool>(true, lexer.location()); 
			}
			if(auto token = lexer.match(TT::FALSE)) {
				return std::make_unique<ast::Bool>(false, lexer.location()); 
			}
			return nullptr;
		}

		std::unique_ptr<ast::Literal> array(lex::Lexer & lexer) {
			if(lexer.match(TT::BRACKET_L)) {
				std::vector<std::unique_ptr<ast::Expression>> initElements;
				if(!lexer.match(TT::BRACKET_R)) {
					while(true) {
						if(lexer.match(TT::___EOF___)) {
							throw expected("]", lexer);
						}
						initElements.push_back(expression(lexer));
						const bool comma = !!lexer.match(TT::COMMA);
						if(lexer.match(TT::BRACKET_R)) break;
						if(!comma) {
							throw expected(",", lexer);
						}
					}
				}
				return std::make_unique<ast::Array>(
					std::move(initElements),
					lexer.location());
			}
			return nullptr;
		}

		std::unique_ptr<ast::Literal> string(lex::Lexer & lexer) {
			if(auto token = lexer.match(TT::STRING)) {
				return std::make_unique<ast::String>(token->str, lexer.location()); 
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

		std::pair<std::string, ast::Namespace>
		symbol(lex::Lexer & lexer) {
			ast::Namespace nameSpace;
			if(lexer.match(TT::COLONx2)) {
				nameSpace.push_back("::");
			}
			if(const auto & identifier = lexer.match(TT::INDENTIFIER)) {
				nameSpace.push_back(identifier->str);
				std::string name = identifier->str;
				while(lexer.match(TT::COLONx2)) {
					if(auto i = lexer.match(TT::INDENTIFIER)) {
						nameSpace.push_back(i->str);
						name = i->str;
					}
				}
				nameSpace.pop_back();
				return {name, nameSpace};
			}
			throw expected("indentifier", lexer);
		}

		std::unique_ptr<ast::Call> call(
			const auto & name,
			const auto & nameSpace,
			lex::Lexer & lexer) {
			auto parameters = parse::parameters(lexer);
			return std::make_unique<ast::Call>(
				name,
				nameSpace,
				std::move(parameters),
				lexer.location());
			return nullptr;
		}

		std::unique_ptr<ast::Var> var(
			const auto & name,
			const auto & nameSpace,
			const auto & lexer) {
			if(nameSpace.empty()) {
				return std::make_unique<ast::Var>(name, lexer.location());
			}
			else {
				throw CompilerError{
					"cannot address variable with namespace in front",
					lexer.location()};
			}
		}

		std::vector<std::string> memberpath(lex::Lexer & lexer) {
			std::vector<std::string> path;
			while(lexer.match(TT::DOT)) {
				if(auto member = lexer.match(TT::INDENTIFIER)) {
					path.push_back(member->str);
				}
				else {
					throw CompilerError{
						"Expected identifier for member access",
						lexer.location()};
				}
			}
			return path;
		}

		std::unique_ptr<ast::Expression> identifier(lex::Lexer & lexer) {
			const auto [name, nameSpace] = symbol(lexer);
			if(lexer.match(TT::PAREN_L)) {
				return call(name, nameSpace, lexer);
			}
			auto var = parse::var(name, nameSpace, lexer);
			auto path = parse::memberpath(lexer);
			if(path.empty()) {
				return var;
			}
			else {
				return std::make_unique<ast::MemberAccess>(
					std::move(var),
					std::move(path),
					lexer.location());
			}
		}

		std::unique_ptr<ast::FxPointer> fxPointer(lex::Lexer & lexer) {
			if(lexer.match(TT::AMPERSAND)) {
				const auto [name, nameSpace] = symbol(lexer);
				if(lexer.match(TT::PAREN_L)) {
					const auto placeholders = parse::placeholder(lexer);
					return std::make_unique<ast::FxPointer>(
						name, nameSpace, placeholders, lexer.location());
				}
				throw expected("(", lexer);
			}
			return nullptr; 
		}
	}

	// parses primary expression
	std::unique_ptr<ast::Expression> primary(lex::Lexer & lexer) {
		if(auto expr = integerDec(lexer)) return expr;
		if(auto expr = integerBin(lexer)) return expr;
		if(auto expr = integerHex(lexer)) return expr;
		if(auto expr = character(lexer)) return expr;
		if(auto expr = floating(lexer)) return expr;
		if(auto expr = boolean(lexer)) return expr;
		if(auto expr = null(lexer)) return expr;
		if(auto expr = paren(lexer)) return expr;
		if(auto expr = string(lexer)) return expr;
		if(auto expr = array(lexer)) return expr;
		if(auto expr = fxPointer(lexer)) return expr;
		if(auto expr = lambda(lexer)) return expr;
		return identifier(lexer);
	}
}

