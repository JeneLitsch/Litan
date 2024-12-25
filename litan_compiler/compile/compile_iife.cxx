#include "compile.hxx"
#include <string_view>
#include "litan_compiler/sst/expr/Iife.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::Iife & iife) {
		InstructionBuffer buf;
		buf << compile_statement(*iife.stmt);
		buf << inst::null();
		buf << inst::label(iife.return_label);
		return buf;
	}
}