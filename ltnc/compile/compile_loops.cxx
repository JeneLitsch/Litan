#include "compile.hxx"

namespace ltn::c::compile {
	StmtCode while_loop(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loop_scope{&scope}; 
		
		// compile parts
		const auto condition = expression(*stmt.condition, info, scope);
		const auto body = statement(*stmt.body, info, loop_scope);
		const auto begin = make_jump_id("WHILE_BEGIN", info);
		const auto end = make_jump_id("WHILE_END", info);

		// generate asm code
		std::stringstream ss;
		ss 	<< inst::jumpmark(begin)
			<< condition.code
			<< inst::ifelse(end)
			<< body.code
			<< inst::jump(begin)
			<< inst::jumpmark(end);

		return {ss.str(), body.var_count};
	}



	StmtCode infinite_loop(const ast::InfiniteLoop & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loop_scope{&scope}; 
		
		// compile parts
		const auto body = statement(*stmt.body, info, loop_scope);
		const auto jump = make_jump_id("INFINETE_LOOP", info);

		// generate asm code
		std::stringstream ss;
		ss 	<< inst::jumpmark(jump)
			<< body.code
			<< inst::jump(jump);

		return {ss.str(), body.var_count};
	}



	StmtCode for_loop(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loop_scope{&scope};

		// compile parts
		const auto var = new_const(*stmt.var, info, loop_scope);
		const auto from = expression(*stmt.from, info, loop_scope);
		const auto to = expression(*stmt.to, info, loop_scope);
		const auto body = statement(*stmt.body, info, loop_scope);
		const auto begin = make_jump_id("FOR_BEGIN", info);
		const auto end = make_jump_id("FOR_END", info);

		// get address of index var
		const auto iVar = loop_scope.resolve(stmt.var->name, stmt.location);
				
		std::stringstream ss;
		
		// Init
		ss << from.code;
		ss << inst::write_x(iVar.address);

		// Condition
		ss << inst::jumpmark(begin);
		ss << inst::read_x(iVar.address);
		ss << to.code;
		ss << inst::sml;
		ss << inst::ifelse(end);

		// body
		ss << body.code;

		// Increments
		ss << inst::read_x(iVar.address);
		if(stmt.step) {
			ss << expression(*stmt.step, info, loop_scope).code;
			ss << inst::add;
		}
		else {
			ss << inst::inc;
		}
		ss << inst::write_x(iVar.address);

		// End of loop
		ss << inst::jump(begin);
		ss << inst::jumpmark(end);

		return StmtCode{ss.str(), body.var_count + 1};
	}

}