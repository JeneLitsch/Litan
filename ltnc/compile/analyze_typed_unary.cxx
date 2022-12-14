#include "compile.hxx"
#include "ltnc/compile/cast_static.hxx"
// #include "ltnc/compile/cast_dynamic.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr actual(
			const auto & actual_copy,
			const auto & deduce_type,
			const auto & copy,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto outer = actual_copy(inner.deduced_type, type, copy.location);

			InstructionBuffer buf;
			buf << inner.code;
			buf << outer; 

			return sst::expr_ptr {
				.code = buf,
				.deduced_type = deduce_type(type),
			};
		}

		type::Type deduce_type(sst::TypedUnary::Op op, const type::Type & target_type) {
			switch (op) {
			case sst::TypedUnary::Op::STATIC_COPY: return type::deduce_copy_static(target_type);
			case sst::TypedUnary::Op::DYNAMIC_COPY: return type::deduce_copy_dynamic(target_type);
			case sst::TypedUnary::Op::STATIC_CAST: return deduce_cast_static(target_type);
			case sst::TypedUnary::Op::DYNAMIC_CAST: return deduce_cast_dynamic(target_type);
			}
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::TypedUnary & tunary,
		CompilerInfo & info,
		Scope & scope) {
		const auto expr = analyze_expression(*tunary.expr, info, scope);
		const auto target_type = instantiate_type(tunary.type, scope);
		const auto op = static_cast<sst::TypedUnary::Op>(tunary.op);
		const auto type = deduce_type(op, target_type);
		return std::make_unique<sst::TypedUnary>(op, target_type, std::move(expr), type);
	}
}