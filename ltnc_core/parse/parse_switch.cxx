#include "parse.hxx"
#include "ltnc_core/CompilerError.hxx"

namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
	}

	template<typename NodeT, TT START_TOKEN, auto body_fx>
	std::unique_ptr<NodeT> any_switch(lex::Lexer & lexer) {
		if(lexer.match(START_TOKEN)) {
			if(!lexer.match(TT::PAREN_L)) throw CompilerError {
				"Expected (", lexer.location()
			};

			auto sw1tch = std::make_unique<NodeT>(lexer.location());
			sw1tch->condition = parse::expression(lexer);

			if(!lexer.match(TT::PAREN_R)) throw CompilerError {
				"Expected )", lexer.location()
			};

			if(!lexer.match(TT::BRACE_L)) throw CompilerError {
				"Expected {", lexer.location()
			};

			while (lexer.match(TT::CASE)) {
				auto case_expr = parse::static_expression(lexer);
				
				if(!lexer.match(TT::COLON)) throw CompilerError {
					"Expected :", lexer.location()
				};

				auto case_body = body_fx(lexer);

				sw1tch->cases.push_back(std::pair{
					std::move(case_expr),
					std::move(case_body)});

				while (lexer.match(TT::SEMICOLON));
			}
			
			if(lexer.match(TT::DEFAULT)) {
				if(!lexer.match(TT::COLON)) throw CompilerError {
					"Expected :", lexer.location()
				};
				sw1tch->d3fault = body_fx(lexer);
				while (lexer.match(TT::SEMICOLON));
			}

			if(!lexer.match(TT::BRACE_R)) throw CompilerError {
				"Expected }", lexer.location()
			};


			return sw1tch;
		}
		return nullptr;
	} 



	ast::stmt_ptr stmt_switch(lex::Lexer & lexer) {
		auto sw1tch = any_switch<ast::StmtSwitch, TT::SWITCH, parse::statement>(lexer);
		if(sw1tch && !sw1tch->d3fault) {
			sw1tch->d3fault = std::make_unique<ast::DoNothing>(lexer.location());
		}
		return sw1tch;
	} 



	ast::expr_ptr expr_switch(lex::Lexer & lexer) {
		auto sw1tch = any_switch<ast::ExprSwitch, TT::CHOOSE, parse::expression>(lexer);
		if(sw1tch && !sw1tch->d3fault) {
			sw1tch->d3fault = std::make_unique<ast::Null>(lexer.location());
		}
		return sw1tch;
	}
}