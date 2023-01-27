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
			auto binding = std::make_unique<ast::BraceBinding>(start.location);
			
			const auto add_var = [&] (const auto & name) {
				auto var_bind = std::make_unique<ast::VarBinding>(
					start.location,
					name
				);
				binding->sub_bindings.push_back(std::move(var_bind));
			};

			add_var(parse_variable_name(tokens));
			while(match(TT::COMMA, tokens)) {
				add_var(parse_variable_name(tokens));
			}
			if(!match(TT::PAREN_R, tokens)) throw CompilerError {
				"Expected )", start.location
			};
			auto && r = parse_assign_r(tokens);
			if(!r) throw CompilerError {
				"Structure bindings must be assigned", start.location
			};
			semicolon(tokens);
			return std::make_unique<ast::StructuredBinding>(
				std::move(binding),
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