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
		Scope loopScope{&scope};

		const auto var = newVar(*stmt.var, info, loopScope);
		const auto from = expression(*stmt.from, info, loopScope);
		const auto to = expression(*stmt.to, info, loopScope);
		const auto body = statement(*stmt.body, info, loopScope);
		const auto begin = makeJumpId("FOR_BEGIN", info);
		const auto end = makeJumpId("FOR_END", info);
		
		const auto iVar = loopScope.resolve(stmt.var->name, stmt.debugInfo.line);
				
		std::stringstream ss;
		
		// Init
		ss << var.code;
		ss << from.code;
		ss << inst::addr(iVar);
		ss << inst::write;

		// Condition
		ss << inst::jumpmark(begin);
		ss << inst::addr(iVar);
		ss << inst::read;
		ss << to.code;
		ss << inst::sml;
		ss << inst::ifelse(end);

		// body
		ss << body.code;

		// Increments
		ss << inst::addr(iVar);
		ss << inst::read;
		ss << inst::inc;
		ss << inst::addr(iVar);
		ss << inst::write;

		// End of loop
		ss << inst::jump(begin);
		ss << inst::jumpmark(end);

		return StmtCode{ss.str()};
	}

}