#include "compile.hxx"

namespace ltn::c::compile {
	std::string jump_begin(const std::string & name) {
		return name + "_BEGIN";
	}

	std::string jump_end(const std::string & name) {
		return name + "_END";
	}

	std::string var_from(const std::string & name) {
		return name + "_FROM";
	}

	std::string var_to(const std::string & name) {
		return name + "_TO";
	}

	StmtCode while_loop(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loop_scope{&scope}; 
		
		// compile parts
		const auto condition = expression(*stmt.condition, info, scope);
		const auto body = statement(*stmt.body, info, loop_scope);
		const auto name = make_jump_id("WHILE");
		const auto begin = jump_begin(name);
		const auto end = jump_end(name);

		// generate asm code
		std::stringstream ss;
		ss 
			<< inst::jumpmark(begin)
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
		const auto jump = make_jump_id("INFINETE_LOOP");

		// generate asm code
		std::stringstream ss;
		ss
			<< inst::jumpmark(jump)
			<< body.code
			<< inst::jump(jump);

		return {ss.str(), body.var_count};
	}


	StmtCode for_loop(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		Scope loop_scope{&scope};

		const auto var = new_variable(*stmt.var, info, loop_scope);
		const auto from = expression(*stmt.from, info, loop_scope);
		const auto to = expression(*stmt.to, info, loop_scope);
		
		const auto name = make_jump_id("FOR");
		const auto begin = jump_begin(name);
		const auto end = jump_end(name);

		const auto i_var    = loop_scope.resolve(stmt.var->name, stmt.location);
		const auto from_var = loop_scope.insert(var_from(name), stmt.location);
		const auto to_var   = loop_scope.insert(var_to(name), stmt.location);

		const auto body = statement(*stmt.body, info, loop_scope);
				
		std::stringstream ss;
		
		// Init
		ss
			<< to.code
			<< from.code
			<< inst::duplicate
			<< inst::write_x(i_var.address)
			<< inst::write_x(from_var.address)
			<< inst::write_x(to_var.address);

		// Condition
		ss
			<< inst::jumpmark(begin)
			<< inst::read_x(to_var.address)
			<< inst::read_x(from_var.address)
			<< inst::read_x(i_var.address)
			<< inst::between
			<< inst::ifelse(end);

		// body
		ss << body.code;

		// Increments
		ss << inst::read_x(i_var.address);
		if(auto & step = stmt.step) {
			ss
				<< expression(*step, info, loop_scope).code
				<< inst::add;
		}
		else {
			ss << inst::inc;
		}
		ss << inst::write_x(i_var.address);

		// End of loop
		ss
			<< inst::jump(begin)
			<< inst::jumpmark(end);

		return StmtCode{ss.str(), body.var_count + 3};
	}
}