#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::InitMember & stmt,
		CompilerInfo & info,
		Scope & scope) {

		const auto obj = scope.resolve("___OBJ___", stmt.location);
		const auto var = scope.resolve(stmt.param, stmt.location);
		const auto mem = info.member_table.get_id(stmt.member);
		
		return std::make_unique<sst::InitMember>(
			std::size_t{0}, false,
			obj->address,
			mem,
			var->address,
			type::Any{}
		);
	}
}