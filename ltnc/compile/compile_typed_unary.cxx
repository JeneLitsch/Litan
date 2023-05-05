// #include "compile.hxx"
// #include "ltnc/type/encode.hxx"
// #include "ltnc/type/traits.hxx"

// namespace ltn::c {
// 	namespace {
// 		InstructionBuffer actual(
// 			const auto & inst,
// 			const auto & copy) {
			
// 			const auto inner = compile_expression(*copy.expr);
// 			const auto outer 
// 				= type::is_any(copy.target_type)
// 				? InstructionBuffer{}
// 				: InstructionBuffer{inst(type::encode_type(copy.target_type))};

// 			InstructionBuffer buf;
// 			buf << inner;
// 			buf << outer; 

// 			return buf;
// 		}
// 	}



// 	InstructionBuffer compile_expr(const sst::TypedUnary & expr) {
// 		using Op = sst::TypedUnary::Op;

// 		switch (expr.op) {
// 		case Op::CONVERSION:   return actual(inst::conversion, expr);
// 		case Op::STATIC_CAST:  return actual(inst::cast, expr);
// 		case Op::DYNAMIC_CAST: return actual(inst::safe_cast, expr);
// 		case Op::FORCE_CAST:   return actual(inst::cast, expr);
// 		case Op::STATIC_COPY:  return actual(inst::copy, expr);
// 		case Op::DYNAMIC_COPY: return actual(inst::safe_copy, expr);
// 		case Op::FORCE_COPY:   return actual(inst::copy, expr);
// 		default: throw std::runtime_error{"Invalid TypedUnary::Op"};
// 		}
// 	}
// }