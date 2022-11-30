#include "compile.hxx"

namespace ltn::c {
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

	StmtResult compile_stmt(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		MinorScope loop_scope { &scope }; 
		
		// compile parts
		const auto condition = compile_expression(*stmt.condition, info, scope);
		const auto body = compile_statement(*stmt.body, info, loop_scope);
		const auto name = make_jump_id("WHILE");
		const auto begin = jump_begin(name);
		const auto end = jump_end(name);

		// generate asm code
		InstructionBuffer buf;
		buf 
			<< inst::label(begin)
			<< condition.code
			<< inst::ifelse(end)
			<< body.code
			<< inst::jump(begin)
			<< inst::label(end);

		return { buf, body.var_count };
	}



	StmtResult compile_stmt(const ast::InfiniteLoop & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		MinorScope loop_scope { &scope }; 
		
		// compile parts
		const auto body = compile_statement(*stmt.body, info, loop_scope);
		const auto jump = make_jump_id("INFINETE_LOOP");

		// generate asm code
		InstructionBuffer buf;
		buf
			<< inst::label(jump)
			<< body.code
			<< inst::jump(jump);

		return { buf, body.var_count};
	}



	StmtResult compile_stmt(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		MinorScope loop_scope { &scope };

		const auto var = compile_statement(*stmt.var, info, loop_scope);
		const auto from = compile_expression(*stmt.from, info, loop_scope);
		const auto to = compile_expression(*stmt.to, info, loop_scope);
		
		const auto name = make_jump_id("FOR");
		const auto begin = jump_begin(name);
		const auto end = jump_end(name);

		const auto i_var    = loop_scope.resolve(stmt.var->name, stmt.location);
		const auto from_var = loop_scope.insert(var_from(name), stmt.location);
		const auto to_var   = loop_scope.insert(var_to(name), stmt.location);

		const auto body = compile_statement(*stmt.body, info, loop_scope);
				
		InstructionBuffer buf;
		
		// Init
		buf
			<< to.code
			<< from.code
			<< inst::duplicate()
			<< inst::write_x(i_var->address)
			<< inst::write_x(from_var.address)
			<< inst::write_x(to_var.address);

		// Condition
		buf
			<< inst::label(begin)
			<< inst::read_x(to_var.address)
			<< inst::read_x(from_var.address)
			<< inst::read_x(i_var->address)
			<< inst::between()
			<< inst::ifelse(end);

		// body
		buf << body.code;

		// Increments
		buf << inst::read_x(i_var->address);
		if(auto & step = stmt.step) {
			buf
				<< compile_expression(*step, info, loop_scope).code
				<< inst::add();
		}
		else {
			buf << inst::inc();
		}
		buf << inst::write_x(i_var->address);

		// End of loop
		buf
			<< inst::jump(begin)
			<< inst::label(end);

		return StmtResult{ buf, body.var_count + 3 };
	}
}