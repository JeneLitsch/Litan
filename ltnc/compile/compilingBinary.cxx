#include "compiling.hxx"

namespace ltn::c::compile {

	std::string_view getBinInst(ast::Binary::Type op) {
		switch (op) {
		case ast::Binary::Type::ADD: return inst::add;
		case ast::Binary::Type::SUB: return inst::sub;
		case ast::Binary::Type::MLT: return inst::mlt;
		case ast::Binary::Type::DIV: return inst::div;
		case ast::Binary::Type::MOD: return inst::mod;
		case ast::Binary::Type::SMALLER: return inst::sml;
		case ast::Binary::Type::BIGGER: return inst::bgr;
		case ast::Binary::Type::SMALLEREQUAL: return inst::smleql;
		case ast::Binary::Type::BIGGEREQUAL: return inst::bgreql;
		case ast::Binary::Type::EQUAL: return inst::eql;
		case ast::Binary::Type::UNEQUEL: return inst::ueql;
		case ast::Binary::Type::SHIFT_L: return inst::shift_l;
		case ast::Binary::Type::SHIFT_R: return inst::shift_r;
		}
		throw CompilerError{"Invalid binary operation", 0};
	}

	ExprCode binary(const ast::Binary & binary, CompilerInfo & info, Scope & scope) {
		const auto l = compile::expression(*binary.l, info, scope);
		const auto r = compile::expression(*binary.r, info, scope);

		std::stringstream ss;
		ss << l.code;
		ss << r.code;
		ss << getBinInst(binary.type);
		return { ss.str(), false, l.constant && r.constant };
	}
	
}