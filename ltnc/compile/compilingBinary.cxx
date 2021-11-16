#include "compiling.hxx"

namespace ltn::c::compile {
	type::Type mergeTypes(const type::Type & typeL, const type::Type & typeR) {
		if(typeL == typeR) {
			if(type::isVoid(typeL)) {
				throw CompilerError{"Void type not allowed in binary operation", 0};
			}
			return typeL;
		}
		std::stringstream ss;
		ss	<< "Types do not match: " 
			<< typeL
			<< " != "
			<< typeR;
		throw CompilerError{ ss.str(), 0 };
	}

	std::string_view getBinInst(const type::Type & type, ast::Binary::Type op) {
		if(type::isInt(type)) {
			switch (op) {
			case ast::Binary::Type::ADD: return inst::addi;
			case ast::Binary::Type::SUB: return inst::subi;
			case ast::Binary::Type::MLT: return inst::mlti;
			case ast::Binary::Type::DIV: return inst::divi;
			case ast::Binary::Type::MOD: return inst::modi;
			case ast::Binary::Type::SMALLER: return inst::smli;
			case ast::Binary::Type::BIGGER: return inst::bgri;
			case ast::Binary::Type::SMALLEREQUAL: return inst::smleqli;
			case ast::Binary::Type::BIGGEREQUAL: return inst::bgreqli;
			case ast::Binary::Type::EQUAL: return inst::eqli;
			case ast::Binary::Type::UNEQUEL: return inst::ueqli;
			}
		}

		if(type::isFloat(type)) {
			switch (op) {
			case ast::Binary::Type::ADD: return inst::addf;
			case ast::Binary::Type::SUB: return inst::subf;
			case ast::Binary::Type::MLT: return inst::mltf;
			case ast::Binary::Type::DIV: return inst::divf;
			case ast::Binary::Type::MOD: return inst::modf;
			case ast::Binary::Type::SMALLER: return inst::smlf;
			case ast::Binary::Type::BIGGER: return inst::bgrf;
			case ast::Binary::Type::SMALLEREQUAL: return inst::smleqlf;
			case ast::Binary::Type::BIGGEREQUAL: return inst::bgreqlf;
			case ast::Binary::Type::EQUAL: return inst::eqlf;
			case ast::Binary::Type::UNEQUEL: return inst::ueqlf;
			}
		}
		throw CompilerError{"Invalid binary operation", 0};
	}

	ExprCode binary(const ast::Binary & binary, CompilerInfo & info) {
		const auto l = compile::expression(*binary.l, info);
		const auto r = compile::expression(*binary.l, info);
		const auto resultType = mergeTypes(l.type, r.type);

		std::stringstream ss;
		ss << l.code;
		ss << getBinInst(resultType, binary.type);
		ss << r.code;
		return { ss.str(), false, l.constant && r.constant, resultType};
	}
	
}