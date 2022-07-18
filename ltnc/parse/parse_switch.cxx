#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	template<typename NodeT, TT START_TOKEN, auto body_fx>
	std::unique_ptr<NodeT> parse_any_switch(Tokens & tokens) {
		if(match(START_TOKEN, tokens)) {
			if(!match(TT::PAREN_L, tokens)) throw CompilerError {
				"Expected (", tokens.location()
			};

			auto sw1tch = std::make_unique<NodeT>(tokens.location());
			sw1tch->condition = parse_expression(tokens);

			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected )", tokens.location()
			};

			if(!match(TT::BRACE_L, tokens)) throw CompilerError {
				"Expected {", tokens.location()
			};

			while (match(TT::CASE, tokens)) {
				auto case_expr = parse_static_expression(tokens);
				
				if(!match(TT::COLON, tokens)) throw CompilerError {
					"Expected :", tokens.location()
				};

				auto case_body = body_fx(tokens);

				sw1tch->cases.push_back(std::pair{
					std::move(case_expr),
					std::move(case_body)});

				while (match(TT::SEMICOLON, tokens));
			}
			
			if(match(TT::DEFAULT, tokens)) {
				if(!match(TT::COLON, tokens)) throw CompilerError {
					"Expected :", tokens.location()
				};
				sw1tch->d3fault = body_fx(tokens);
				while (match(TT::SEMICOLON, tokens));
			}

			if(!match(TT::BRACE_R, tokens)) throw CompilerError {
				"Expected }", tokens.location()
			};


			return sw1tch;
		}
		return nullptr;
	} 



	ast::stmt_ptr parse_stmt_switch(Tokens & tokens) {
		auto sw1tch = parse_any_switch<ast::StmtSwitch, TT::SWITCH, parse_statement>(tokens);
		if(sw1tch && !sw1tch->d3fault) {
			sw1tch->d3fault = std::make_unique<ast::DoNothing>(tokens.location());
		}
		return sw1tch;
	} 



	ast::expr_ptr parse_expr_switch(Tokens & tokens) {
		auto sw1tch = parse_any_switch<ast::ExprSwitch, TT::CHOOSE, parse_expression>(tokens);
		if(sw1tch && !sw1tch->d3fault) {
			sw1tch->d3fault = std::make_unique<ast::Null>(tokens.location());
		}
		return sw1tch;
	}
}