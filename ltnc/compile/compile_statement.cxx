#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::stmt::NoOp &) {
		return {};
	}



	InstructionBuffer compile_statement(const sst::stmt::Statement & stmt) {
		auto fx = [] (const auto & s) { return compile_stmt(s); };
		return sst::stmt::visit(stmt, fx);
	}
}