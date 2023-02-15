#include "analyze.hxx"
#include <iostream>
#include <sstream>
#include "ltnc/type/traits.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {
		type::Type deduce_type(
			sst::Binary::Op op,
			const type::Type & l,
			const type::Type & r) {
			using OP = BinaryOp;
			switch (op) {
				case OP::ADD:          return type::deduce_add(l, r);
				case OP::SUB:          return type::deduce_sub(l, r);
				case OP::MLT:          return type::deduce_mlt(l, r);
				case OP::DIV:          return type::deduce_div(l, r);
				case OP::MOD:          return type::deduce_mod(l, r);
				case OP::POW:          return type::deduce_pow(l, r);
				case OP::SMALLER:      return type::deduce_compare(l, r);
				case OP::BIGGER:       return type::deduce_compare(l, r);
				case OP::SMALLEREQUAL: return type::deduce_compare(l, r);
				case OP::BIGGEREQUAL:  return type::deduce_compare(l, r);
				case OP::EQUAL:        return type::deduce_compare(l, r);
				case OP::UNEQUEL:      return type::deduce_compare(l, r);
				case OP::SPACE_SHIP:   return type::deduce_three_way(l, r);
				case OP::SHIFT_L:      return type::deduce_bitwise(l, r);
				case OP::SHIFT_R:      return type::deduce_bitwise(l, r);
				case OP::BIT_AND:      return type::deduce_bitwise(l, r);
				case OP::BIT_OR:       return type::deduce_bitwise(l, r);
				case OP::BIT_XOR:      return type::deduce_bitwise(l, r);
				case OP::AND:          return type::deduce_logic(l, r);
				case OP::OR:           return type::deduce_logic(l, r);
				case OP::ELVIS:        return type::deduce_elvis(l, r);
				case OP::NULLCO:       return type::deduce_nullco(l, r);
				default: throw std::runtime_error{"Invalid Binary::Op"};
			}
		}



		CompilerError invalid_operands(
			const type::Type & l,
			const type::Type & r,
			const SourceLocation & location) {
			std::ostringstream oss;
			oss 
				<< "Invalid operands ("
				<< to_string(l) << " and " << to_string(r)
				<< ") for binary expression";

			return CompilerError { oss.str(), location };
		}
	}



	// compiles a binary operation
	sst::expr_ptr analyze_expr(
		const ast::Binary & binary,
		Context & context,
		Scope & scope) {
		
		auto l = analyze_expression(binary.l, context, scope);
		auto r = analyze_expression(binary.r, context, scope);
		const auto op = binary.op;
		const auto type = deduce_type(op, l->type, r->type);

		if(is_error(type)) {
			throw invalid_operands(l->type, r->type, binary.location);
		} 

		return std::make_unique<sst::Binary>(
			op,
			std::move(l),
			std::move(r),
			type
		);
	}
}