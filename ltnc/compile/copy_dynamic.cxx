#include <sstream>
#include "stdxx/array.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/compile/copy_dynamic.hxx"
#include "ltnc/compile/cast_utils.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/type/encode.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	InstructionBuffer copy_dynamic(
		const type::Type &,
		const type::Type & to,
		const SourceLocation & location) {
		return { inst::safe_copy(type::encode_type(to)) };
	}
}