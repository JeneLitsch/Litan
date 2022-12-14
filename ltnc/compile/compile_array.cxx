#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles array literal
	InstructionBuffer compile_expr(const sst::Array & array, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		type::Array array_type;
		for(const auto & elem : array.elements) {
			const auto result = compile_expression(*elem, info, scope);
			buf << result.code;
			array_type = type::deduce_array_append(array_type, result.deduced_type);
		}
		buf << inst::newarr(array.elements.size());
		return InstructionBuffer{ 
			.code = buf,
			.deduced_type = type::Type{array_type} ,
		};
	}
}