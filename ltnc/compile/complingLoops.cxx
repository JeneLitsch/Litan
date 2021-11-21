#include "compiling.hxx"

namespace ltn::c::compile {
	StmtCode whileLoop(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		const auto condition = expression(*stmt.condition, info, scope);
		const auto body = statement(*stmt.body, info, scope);
		const auto begin = makeJumpId("WHILE_BEGIN", info);
		const auto end = makeJumpId("WHILE_END", info);

		std::stringstream ss;
		ss 	<< inst::jumpmark(begin)
			<< condition.code
			<< inst::ifelse(end)
			<< body.code
			<< inst::jump(begin)
			<< inst::jumpmark(end);

		return {ss.str()};
	}
}