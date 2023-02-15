#include "parse.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;
	}

	template<typename NodeT, TT START_TOKEN, auto body_fx>
	std::unique_ptr<NodeT> parse_any_switch(Tokens & tokens) {
		if(match(START_TOKEN, tokens)) {
			if(!match(TT::PAREN_L, tokens)) throw CompilerError {
				"Expected (", location(tokens)
			};

			auto sw1tch = stx::make_unique<NodeT>(location(tokens));
			sw1tch->condition = parse_expression(tokens);

			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected )", location(tokens)
			};

			if(!match(TT::BRACE_L, tokens)) throw CompilerError {
				"Expected {", location(tokens)
			};

			while (match(TT::CASE, tokens)) {
				auto case_expr = parse_expression(tokens);
				
				if(!match(TT::DRARROW, tokens)) throw CompilerError {
					"Expected :", location(tokens)
				};

				auto case_body = body_fx(tokens);

				sw1tch->cases.push_back({});
				sw1tch->cases.back().first = std::move(case_expr);
				sw1tch->cases.back().second = std::move(case_body);

				while (match(TT::SEMICOLON, tokens));
			}
			
			if(match(TT::DEFAULT, tokens)) {
				if(!match(TT::DRARROW, tokens)) throw CompilerError {
					"Expected :", location(tokens)
				};
				sw1tch->d3fault = body_fx(tokens);
				while (match(TT::SEMICOLON, tokens));
			}

			if(!match(TT::BRACE_R, tokens)) throw CompilerError {
				"Expected }", location(tokens)
			};


			return sw1tch;
		}
		return nullptr;
	} 



	ast::stmt_ptr parse_stmt_switch(Tokens & tokens) {
		auto sw1tch = parse_any_switch<ast::StmtSwitch, TT::SWITCH, parse_statement>(tokens);
		if(sw1tch && !sw1tch->d3fault) {
			sw1tch->d3fault = stx::make_unique<ast::DoNothing>(location(tokens));
		}
		return sw1tch;
	} 



	ast::Expression parse_expr_switch(Tokens & tokens) {
		auto sw1tch = parse_any_switch<ast::ExprSwitch, TT::CHOOSE, parse_expression>(tokens);
		if(sw1tch && !sw1tch->d3fault) {
			sw1tch->d3fault = stx::make_unique<ast::Null>(location(tokens));
		}
		return ast::Expression(std::move(sw1tch));
	}
}