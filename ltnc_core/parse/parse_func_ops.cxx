#include "parse.hxx"
#include <sstream>
namespace ltn::c::parse {
	namespace {
		using TT = ltn::c::lex::Token::Type;
		using OP = ltn::c::ast::Binary::Type;

		struct chain_table {
			static const inline auto data = std::array {
				std::pair{TT::CHAIN_R, OP::CHAIN_R}
			};
		};

		struct pipe_table {
			static const inline auto data = std::array {
				std::pair{TT::PIPE_R, OP::PIPE_R}
			};
		};

		template<auto presedence_down>
		ast::expr_ptr functional_op_base(lex::Lexer & lexer) {
			static constexpr auto chain = generic_binary<chain_table, presedence_down>;
			static constexpr auto pipe  = generic_binary<pipe_table,  chain>;
			return pipe(lexer);
		}
	}



	ast::expr_ptr functional_op(lex::Lexer & lexer) {
		return functional_op_base<conditional>(lexer);
	}



	ast::expr_ptr static_functional_op(lex::Lexer & lexer) {
		return functional_op_base<static_conditional>(lexer);
	}
}

