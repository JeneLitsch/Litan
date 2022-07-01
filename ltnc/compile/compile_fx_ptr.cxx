#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	ExprCode compile_fxPointer(
		const ast::FxPointer & ptr,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto fx = info.fx_table.resolve(
			ptr.name,
			scope.get_namespace(),
			ptr.namespaze,
			ptr.placeholders);

		if(!fx) {
			throw undefined_function(ptr.name, ptr);
		}

		guard_private(*fx, scope.get_namespace(), ptr.location);

		InstructionBuffer buf;
		
		buf << ltn::inst::Newfx{fx->id, ptr.placeholders};

		return { buf };
	}
}