#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "parse_utils.hxx"
namespace ltn::c {
	ast::expr_ptr parse_precedence(Tokens & tokens, Precedence precedence);

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
	}



	ast::expr_ptr parse_index(const Token & begin, Tokens & tokens, ast::expr_ptr l) {
		auto index = parse_index(tokens);
		auto location = ast::location(*index);
		return std::make_unique<ast::Index>(
			std::move(l),
			std::move(index),
			location
		);
	}


	
	ast::expr_ptr parse_member(const Token & begin, Tokens & tokens, ast::expr_ptr l) {
		auto name = parse_member(tokens);
		return std::make_unique<ast::Member>(
			std::move(l),
			name,
			location(tokens)
		);
	}


	
	ast::expr_ptr parse_member_call(const Token & begin, Tokens & tokens, ast::expr_ptr l) {
		auto name = parse_member(tokens);

		if(!match(TT::PAREN_L, tokens)) throw CompilerError {
			"Expected ( after member call"
		};

		auto args = parse_arguments(tokens);
		return std::make_unique<ast::InvokeMember>(
			std::move(l),
			std::move(name),
			std::move(args),
			location(tokens)
		);
	}

	
	ast::expr_ptr parse_call(const Token & begin, Tokens & tokens, ast::expr_ptr l) {
		auto function_args = parse_arguments(tokens);

		return std::make_unique<ast::Call>(
			std::move(l),
			std::move(function_args),
			location(tokens)
		);
	}



	ast::expr_ptr parse_precedence(Tokens & tokens, Precedence precedence) {
		std::cout << "AAA\n";
		ast::expr_ptr expr;

		auto prefix_begin = tokens.front();
		tokens.pop();
		auto prefix_tt = prefix_begin.type;

		auto prefix_rule = get_expr_rule(prefix_tt);
		std::cout << "Token " << prefix_begin.str << "\n";
		if (!prefix_rule || !prefix_rule->prefix) {
			throw CompilerError { "Expected expression", prefix_begin.location };
		}

		expr = (*prefix_rule->prefix)(prefix_begin, tokens);

		auto infix_begin = tokens.front();
		tokens.pop();
		auto infix_rule = get_expr_rule(infix_begin.type);

		while (infix_rule && infix_rule->infix && precedence <= infix_rule->precedence) {
			std::cout << "Token " << infix_begin.str << "\n";
			expr = (*infix_rule->infix)(infix_begin, tokens, std::move(expr));
			infix_begin = tokens.front();
			tokens.pop();
			infix_rule = get_expr_rule(infix_begin.type);
		}

		return expr;
	}


	
	template<OP op>
	std::unique_ptr<ast::Expression> parse_prefix(Tokens & tokens) {
		auto r = parse_precedence(tokens, Precedence::PREFIX_UNARY);
		return std::make_unique<ast::Unary>(op, std::move(r), location(tokens));
	}



	ast::expr_ptr parse_neg(const Token & begin, Tokens & tokens) {
		return parse_prefix<OP::NEG>(tokens);
	}
	ast::expr_ptr parse_not(const Token & begin, Tokens & tokens) {
		return parse_prefix<OP::NOT>(tokens);
	}
	ast::expr_ptr parse_nul(const Token & begin, Tokens & tokens) {
		return parse_prefix<OP::NUL>(tokens);
	}
	ast::expr_ptr parse_bitnot(const Token & begin, Tokens & tokens) {
		return parse_prefix<OP::BITNOT>(tokens);
	}


	std::unique_ptr<ast::Expression> parse_unary(Tokens & tokens) {
		return parse_precedence(tokens, Precedence::PREFIX_UNARY);
	}
}
