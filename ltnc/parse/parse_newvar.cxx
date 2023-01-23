#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;



		ast::stmt_ptr parse_simple_newvar(const Token & start, Tokens & tokens) {
			auto name = parse_variable_name(tokens);
			auto type = parse_var_type_auto(tokens);
			auto && r = parse_assign_r(tokens);
			semicolon(tokens);
			return stx::make_unique<ast::NewVar>(
				name,
				std::move(r),
				location(tokens),
				type
			);
		}



		ast::stmt_ptr parse_unpack_newvar(const Token & start, Tokens & tokens) {
			std::vector<std::string> names;
			names.push_back(parse_variable_name(tokens));
			while(match(TT::COMMA, tokens)) {
				names.push_back(parse_variable_name(tokens));
			}
			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected )", start.location
			};
			auto && r = parse_assign_r(tokens);
			if(!r) throw CompilerError {
				"Structure bindings must be assigned", start.location
			};
			semicolon(tokens);
			return std::make_unique<ast::NewVarUnpack>(
				std::move(names),
				std::move(r),
				start.location
			); 
		}
	}



	ast::stmt_ptr parse_newvar(Tokens & tokens) {
		if(auto start = match(TT::VAR, tokens)) {
			if(match(TT::PAREN_L, tokens)) {
				return parse_unpack_newvar(*start, tokens);
			}
			else {
				return parse_simple_newvar(*start, tokens);
			} 
		}
		return nullptr;
	}
}