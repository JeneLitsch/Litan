#include "compile.hxx"
#include "stdxx/functional.hxx"
#include "stdxx/iife.hxx"
#include <string_view>
#include "litan_compiler/sst/expr/FxPointer.hxx"
#include "litan_compiler/sst/expr/Var.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::FxPointer & fx_ptr) {
		InstructionBuffer buf;
		buf << inst::newfx(fx_ptr.label.to_string());
		for(const auto & capture : fx_ptr.captures) {
			buf << compile_expression(*capture);
			buf << inst::capture();
		}
		return buf;
	}
}