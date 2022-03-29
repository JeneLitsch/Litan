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
		const auto loop_id = make_jump_id("FOR", info);
		const auto begin = loop_id + "_BEGIN";
		const auto end = loop_id + "_END";

		// get address of index var
		const auto i_var    = loop_scope.resolve(stmt.var->name, stmt.location).address;
		const auto from_var = loop_scope.insert("__FROM__" + loop_id, stmt.location).address;
		const auto to_var   = loop_scope.insert("__TO__" + loop_id, stmt.location).address;
		const auto body = statement(*stmt.body, info, loop_scope);
				
		std::stringstream ss;
		
		// Init
		if(stmt.reverse) {
			ss << from.code;
			ss << to.code;
		}
		else {
			ss << to.code;
			ss << from.code;
		}
		ss << inst::duplicate;
		ss << inst::write_x(i_var);
		ss << inst::write_x(from_var);
		ss << inst::write_x(to_var);

		// Condition
		ss << inst::jumpmark(begin);
		ss << inst::read_x(i_var);
		ss << inst::read_x(to_var);
		
		if(stmt.reverse && stmt.closed) {
			ss << inst::bgreql;
		}
		
		else if(stmt.reverse) {
			ss << inst::bgr;
		}

		else if(stmt.closed) {
			ss << inst::smleql;
		}
		
		else {
			ss << inst::sml;
		}

		ss << inst::ifelse(end);

		// body
		ss << body.code;

		// Increments
		ss << inst::read_x(i_var);
		if(stmt.step) {
			ss << expression(*stmt.step, info, loop_scope).code;
			if(stmt.reverse) {
				ss << inst::sub;
			}
			else {
				ss << inst::add;
			}
		}
		else {
			if(stmt.reverse) {
				ss << inst::dec;
			}
			else {
				ss << inst::inc;
			}
		}
		ss << inst::write_x(i_var);

		// End of loop
		ss << inst::jump(begin);
		ss << inst::jumpmark(end);

		return StmtCode{ss.str(), body.var_count + 3};
	}

}