#include "transpile_c.hxx"

namespace ltn::c::trans::c {
	void transpile_c_expr(const sst::Choose &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Ternary &, std::ostream & out, Indent indent) {}

	void transpile_c_expr(const sst::Binary & expr, std::ostream & out, Indent indent) {
		transpile_c_expression(*expr.l, out, indent);
		transpile_c_expression(*expr.r, out, indent);
		using OP = ltn::c::sst::Binary::Op;
		switch (expr.op)
		{
			case OP::ADD:          out << indent << "op_add();\n";          return;
			case OP::SUB:          out << indent << "op_sub();\n";          return;
			case OP::MLT:          out << indent << "op_mlt();\n";          return;
			case OP::DIV:          out << indent << "op_div();\n";          return;
			case OP::MOD:          out << indent << "op_mod();\n";          return;
			case OP::POW:          out << indent << "op_pow();\n";          return;
			case OP::SMALLER:      out << indent << "op_smaller();\n";      return;
			case OP::BIGGER:       out << indent << "op_bigger();\n";       return;
			case OP::SMALLEREQUAL: out << indent << "op_smallerequal();\n"; return;
			case OP::BIGGEREQUAL:  out << indent << "op_biggerequal();\n";  return;
			case OP::EQUAL:        out << indent << "op_equal();\n";        return;
			case OP::UNEQUEL:      out << indent << "op_unequel();\n";      return;
			case OP::SPACE_SHIP:   out << indent << "op_space_ship();\n";   return;
			case OP::SHIFT_L:      out << indent << "op_shift_l();\n";      return;
			case OP::SHIFT_R:      out << indent << "op_shift_r();\n";      return;
			case OP::BIT_AND:      out << indent << "op_bit_and();\n";      return;
			case OP::BIT_OR:       out << indent << "op_bit_or();\n";       return;
			case OP::BIT_XOR:      out << indent << "op_bit_xor();\n";      return;
			case OP::AND:          out << indent << "op_and();\n";          return;
			case OP::OR:           out << indent << "op_or();\n";           return;
			case OP::ELVIS:        out << indent << "op_elvis();\n";        return;
			case OP::NULLCO:       out << indent << "op_nullco();\n";       return;
		}
	}

	void transpile_c_expr(const sst::Unary & expr, std::ostream & out, Indent indent) {
		transpile_c_expression(*expr.expr, out, indent);
		using OP = ltn::c::sst::Unary::Op;
		switch (expr.op) {
			case OP::NEG:    out << indent << "op_neg();\n";    return; 
			case OP::NOT:    out << indent << "op_not();\n";    return; 
			case OP::NUL:    out << indent << "op_nul();\n";    return; 
			case OP::BITNOT: out << indent << "op_bitnot();\n"; return; 
			case OP::DEREF:  out << indent << "op_deref();\n";  return; 
		}
	}

	void transpile_c_expr(const sst::Integer & literal, std::ostream & out, Indent indent) {
		out << indent << "push(value_int(" << literal.value << "));\n"; 
	}

	void transpile_c_expr(const sst::Float & literal, std::ostream & out, Indent indent) {
		out << indent << "push(value_float(" << literal.value << "));\n"; 
	}

	void transpile_c_expr(const sst::Bool & literal, std::ostream & out, Indent indent) {
		out << indent << "push(value_bool(" << literal.value << "));\n"; 
	}

	void transpile_c_expr(const sst::Char & literal, std::ostream & out, Indent indent) {
		out << indent << "push(value_char(" << literal.value << "));\n"; 
	}

	void transpile_c_expr(const sst::Null &, std::ostream & out, Indent indent) {
		out << indent << "push(value_null());\n"; 
	}
	
	void transpile_c_expr(const sst::String &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Array &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Tuple &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Call &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Invoke &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::InvokeMember &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Index &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::FxPointer &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Iife &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Var &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Member &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::GlobalVar &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Reflect &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::InitStruct &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Map &, std::ostream & out, Indent indent) {}
	void transpile_c_expr(const sst::Type &, std::ostream & out, Indent indent) {}

	void transpile_c_expression(const sst::Expression & expr, std::ostream & out, Indent indent) {
		sst::visit_expression(expr, [&] (const auto & e) {
			transpile_c_expr(e, out, indent);
			return 0;
		});
	}
}