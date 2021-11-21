#include "compiling.hxx"

namespace ltn::c::compile {
	StmtCode whileLoop(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		Scope loopScope{&scope}; 
		const auto condition = expression(*stmt.condition, info, scope);
		const auto body = statement(*stmt.body, info, loopScope);
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


	StmtCode forLoop(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		throw CompilerError{"No for loop allowed", stmt.debugInfo.line};
		const auto var = statement(*stmt.var, info, scope);
		const auto from = expression(*stmt.from, info, scope);
		const auto to = expression(*stmt.to, info, scope);
		const auto body = statement(*stmt.body, info, scope);
		const auto begin = makeJumpId("FOR_BEGIN", info);
		const auto end = makeJumpId("FOR_END", info);
	}

}