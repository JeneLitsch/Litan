#include "compiling.hxx"

namespace ltn::c::compile {
	StmtCode whileLoop(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loopScope{&scope}; 
		
		// compile parts
		const auto condition = expression(*stmt.condition, info, scope);
		const auto body = statement(*stmt.body, info, loopScope);
		const auto begin = makeJumpId("WHILE_BEGIN", info);
		const auto end = makeJumpId("WHILE_END", info);

		// generate asm code
		std::stringstream ss;
		ss 	<< inst::jumpmark(begin)
			<< condition.code
			<< inst::ifelse(end)
			<< body.code
			<< inst::jump(begin)
			<< inst::jumpmark(end);

		return {ss.str(), body.varCount};
	}


	StmtCode forLoop(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loopScope{&scope};

		// compile parts
		const auto var = newVar(*stmt.var, info, loopScope);
		const auto from = expression(*stmt.from, info, loopScope);
		const auto to = expression(*stmt.to, info, loopScope);
		const auto body = statement(*stmt.body, info, loopScope);
		const auto begin = makeJumpId("FOR_BEGIN", info);
		const auto end = makeJumpId("FOR_END", info);

		// get address of index var
		const auto iVar = loopScope.resolve(stmt.var->name, stmt.debugInfo.line);
				
		std::stringstream ss;
		
		// Init
		ss << from.code;
		ss << inst::write_x(iVar);

		// Condition
		ss << inst::jumpmark(begin);
		ss << inst::read_x(iVar);
		ss << to.code;
		ss << inst::sml;
		ss << inst::ifelse(end);

		// body
		ss << body.code;

		// Increments
		ss << inst::read_x(iVar);
		ss << inst::inc;
		ss << inst::write_x(iVar);

		// End of loop
		ss << inst::jump(begin);
		ss << inst::jumpmark(end);

		return StmtCode{ss.str(), body.varCount + 1};
	}

}