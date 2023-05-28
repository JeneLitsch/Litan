#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "parse_utils.hxx"
namespace ltn::c {
	namespace {
		using TT = Token::Type;
		using OP = UnaryOp;



		std::variant<std::string, MemberCode> parse_member(Tokens & tokens) {
			if(auto member = match(TT::BRACE_L, tokens)) {
				MemberCode code = parse_member_code(tokens);
				if(!match(TT::BRACE_R, tokens)) {
					throw CompilerError{"Expected }", location(tokens)};
				}
				return code;
			}
			else if(auto member = match(TT::INDENTIFIER, tokens)) {
				return member->str;
			}
			else {
				throw CompilerError {
					"Expected identifier for member access",
					location(tokens)
				};
			}
		}



		std::unique_ptr<ast::Expression> parse_index(Tokens & tokens) {
			auto index = parse_expression(tokens);
			if(match(TT::BRACKET_R, tokens)) {
				return index;
			}
			throw CompilerError{"Missing ]", location(tokens)};
		}



		auto parse_arguments(Tokens & tokens) {
			std::vector<std::unique_ptr<ast::Expression>> parameters;
			if(match(TT::PAREN_R, tokens)) {
				 return parameters;
			}
			while(true) {
				parameters.push_back(parse_expression(tokens));
				if(match(TT::PAREN_R, tokens)) {
					return parameters;
				}
				if(!match(TT::COMMA, tokens)) throw CompilerError {
					"Expected ,", location(tokens)
				};
			}
		}



		std::unique_ptr<ast::Expression> parse_postfix(
			Tokens & tokens,
			std::unique_ptr<ast::Expression> l) {

			if(auto start = match(TT::BRACKET_L, tokens)) {
				auto index = parse_index(tokens);
				auto location = ast::location(*index);
				auto full = std::make_unique<ast::Index>(
					std::move(l),
					std::move(index),
					location
				);
				return parse_postfix(tokens, std::move(full));
			}

			if(auto start = match(TT::DOT, tokens)) {
				auto name = parse_member(tokens);
				auto access = std::make_unique<ast::Member>(
					std::move(l),
					name,
					location(tokens)
				);
				return parse_postfix(tokens, std::move(access));
			}


			if(auto start = match(TT::RARROW, tokens)) {
				auto name = parse_member(tokens);

				if(!match(TT::PAREN_L, tokens)) throw CompilerError {
					"Expected ( after member call"
				};

				auto args = parse_arguments(tokens);
				auto access = std::make_unique<ast::InvokeMember>(
					std::move(l),
					std::move(name),
					std::move(args),
					location(tokens)
				);
				return parse_postfix(tokens, std::move(access));
			}

			if(auto start = match(TT::PAREN_L, tokens)) {

				auto function_args = parse_arguments(tokens);

				auto call = std::make_unique<ast::Call>(
					std::move(l),
					std::move(function_args),
					location(tokens)
				);
				return parse_postfix(tokens, std::move(call));
			}

			return l;
		}
	}



	std::unique_ptr<ast::Expression> parse_prefix(Tokens & tokens) {
		// left unary
		constexpr static std::array table {
			std::pair{TT::MINUS, OP::NEG},
			std::pair{TT::XMARK, OP::NOT},
			std::pair{TT::QMARK, OP::NUL},
			std::pair{TT::TILDE, OP::BITNOT},
		};

		if(auto ref = match(TT::REF, tokens)) {
			auto && r = parse_prefix(tokens);
			return std::make_unique<ast::Ref>(std::move(r), ref->location);
		}

		if(auto deref = match(TT::DEREF, tokens)) {
			auto && r = parse_prefix(tokens);
			return std::make_unique<ast::Deref>(std::move(r), deref->location);
		}
		
		if(auto op = match_op(tokens, table)) {
			auto && r = parse_prefix(tokens);
			return std::make_unique<ast::Unary>(*op, std::move(r), location(tokens));
		}
		return parse_postfix(tokens, parse_primary(tokens));
	}



	std::unique_ptr<ast::Expression> parse_unary(Tokens & tokens) {
		return parse_prefix(tokens);
	}
}
