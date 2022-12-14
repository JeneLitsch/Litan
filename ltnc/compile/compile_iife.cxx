#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	InstructionBuffer compile_expr(const sst::Iife & iife) {
		InstructionBuffer buf;
		buf << compile_statement(*iife.stmt);
		buf << inst::null();
		buf << inst::label(iife.return_label);
		return buf;
	}
}