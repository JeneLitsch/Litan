#include "parse.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/ast/expr/Conditional.hxx"
#include "ltnc/ast/stmt/Conditional.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
		
		auto parse_body(Tokens & tokens, auto parse) {
			if(!match(TT::DRARROW, tokens)) {
				throw CompilerError{"Expected =>", location(tokens)};
			}
			return parse(tokens);
		}



		auto parse_conditional(Tokens & tokens, auto make, auto parse) -> decltype(parse(tokens)) {
			if(auto start = match(TT::CONDITIONAL, tokens)) {
				auto conditional = make(start->location);
				if(match(TT::BRACE_L, tokens)) {
					while(auto case_start = match(TT::CASE, tokens)) {
						auto expr = parse_expression(tokens);
						auto body = parse_body(tokens, parse);
						conditional->add_case(std::move(expr), std::move(body));
					}
					if(match(TT::ELSE, tokens)) {
						auto body = parse_body(tokens, parse);
						conditional->set_else(std::move(body));
					}
					if(match(TT::BRACE_R, tokens)) {
						return conditional;
					}
					else {
						throw CompilerError{"Expected }", start->location};
					}
				}
				else {
					throw CompilerError{"Expected {", start->location};
				}
			}
			return nullptr;
		}
	}



	ast::expr_ptr parse_conditional_expr(Tokens & tokens) {
		return parse_conditional(tokens, ast::expr::conditional, parse_expression);
	}



	ast::stmt_ptr parse_conditional_stmt(Tokens & tokens) {
		auto stmt = parse_conditional(tokens, ast::stmt::conditional, parse_statement);
		return stmt;
	}
}