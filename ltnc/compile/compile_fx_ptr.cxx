#include "compile.hxx"
#include "stdxx/functional.hxx"
#include "stdxx/iife.hxx"
#include <string_view>
#include "ltnc/sst/expr/FxPointer.hxx"
#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::FxPointer & fx_ptr) {
		InstructionBuffer buf;
		const auto arity_code = fx_ptr.arity | std::uint64_t{fx_ptr.is_variadic} << 7;
		buf << inst::newfx(fx_ptr.label.to_string(), arity_code);
		for(const auto & capture : fx_ptr.captures) {
			buf << compile_expression(*capture);
			buf << inst::capture();
		}
		return buf;
	}
}