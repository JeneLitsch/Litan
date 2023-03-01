#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::DoNothing &) {
		return {};
	}



	InstructionBuffer compile_statement(const sst::Statement & stmt) {
		return sst::visit_statement(stmt, [&] (const auto & s) {
			return compile_stmt(s);
		});
	}
}