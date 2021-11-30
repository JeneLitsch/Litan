#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		// map binary operator types to instructions
		std::string_view getBinInst(ast::SimpleBinary::Type op) {
			switch (op) {
			case ast::SimpleBinary::Type::ADD: return inst::add;
			case ast::SimpleBinary::Type::SUB: return inst::sub;
			case ast::SimpleBinary::Type::MLT: return inst::mlt;
			case ast::SimpleBinary::Type::DIV: return inst::div;
			case ast::SimpleBinary::Type::MOD: return inst::mod;
			case ast::SimpleBinary::Type::SMALLER: return inst::sml;
			case ast::SimpleBinary::Type::BIGGER: return inst::bgr;
			case ast::SimpleBinary::Type::SMALLEREQUAL: return inst::smleql;
			case ast::SimpleBinary::Type::BIGGEREQUAL: return inst::bgreql;
			case ast::SimpleBinary::Type::EQUAL: return inst::eql;
			case ast::SimpleBinary::Type::UNEQUEL: return inst::ueql;
			case ast::SimpleBinary::Type::SHIFT_L: return inst::shift_l;
			case ast::SimpleBinary::Type::SHIFT_R: return inst::shift_r;
			}
			throw CompilerError{"Invalid binary operation", 0};
		}

		ExprCode logicalAnd(const auto & l, const auto & r, CompilerInfo & info) {
			const auto id = makeJumpId("AND", info);
			const auto end = id + "_END";
			const auto falsE = id + "_FALSE";
			std::stringstream ss;
			ss << l.code;
			
			ss << inst::ifelse(falsE);
			ss << r.code;
			ss << inst::jump(end);

			ss << inst::jumpmark(falsE);
			ss << inst::falsE;

			ss << inst::jumpmark(end);
			
			return { ss.str() };
		}

		ExprCode logicalOr(const auto & l, const auto & r, CompilerInfo & info) {
			const auto id = makeJumpId("OR", info);
			const auto end = id + "_END";
			const auto truE = id + "_TRUE";
			std::stringstream ss;
			
			ss << l.code;
			ss << inst::n0t;
			ss << inst::ifelse(truE);
			ss << r.code;
			ss << inst::jump(end);

			ss << inst::jumpmark(truE);
			ss << inst::truE;

			ss << inst::jumpmark(end);
			
			
			return { ss.str() };
		}
	}

	// compiles a binary operation
	ExprCode binary(const ast::Binary & binary, CompilerInfo & info, Scope & scope) {
		const auto l = compile::expression(*binary.l, info, scope);
		const auto r = compile::expression(*binary.r, info, scope);

		if(auto bin = as<const ast::SimpleBinary>(binary)) {
			std::stringstream ss;
			ss << l.code;
			ss << r.code;
			ss << getBinInst(bin->type);
			return { ss.str() };
		}
		if(auto logical = as<ast::Logical>(binary)) {
			if(logical->type == ast::Logical::Type::AND) {
				return logicalAnd(l, r, info);
			}
			if(logical->type == ast::Logical::Type::OR) {
				return logicalOr(l, r, info);
			}
		}
		throw CompilerError{"Unknown binary Expr", 0};
	}
	
}