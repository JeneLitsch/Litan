#include "compile.hxx"
#include <sstream>
namespace ltn::c {
	ExprCode compile_read_global(const ast::GlobalVar & definition, CompilerInfo & info) {
		InstructionBuffer buf;
		buf << ltn::inst::GlobalRead { info.global_table.get_id(definition.name) };
		return ExprCode{ buf };
	}
}