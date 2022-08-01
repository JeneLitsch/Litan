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

	StmtCode compile_while_loop(const ast::While & stmt, CompilerInfo & info, Scope & scope) {
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
			<< ltn::inst::Label{begin}
			<< condition.code
			<< ltn::inst::Ifelse{end}
			<< body.code
			<< ltn::inst::Jump{begin}
			<< ltn::inst::Label{end};

		return { buf, body.var_count };
	}



	StmtCode compile_infinite_loop(const ast::InfiniteLoop & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		MinorScope loop_scope { &scope }; 
		
		// compile parts
		const auto body = compile_statement(*stmt.body, info, loop_scope);
		const auto jump = make_jump_id("INFINETE_LOOP");

		// generate asm code
		InstructionBuffer buf;
		buf
			<< ltn::inst::Label{jump}
			<< body.code
			<< ltn::inst::Jump{jump};

		return { buf, body.var_count};
	}



	StmtCode compile_for_loop(const ast::For & stmt, CompilerInfo & info, Scope & scope) {
		// outer scope of loop 
		MinorScope loop_scope { &scope };

		const auto var = compile_new_variable(*stmt.var, info, loop_scope);
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
			<< ltn::inst::Duplicate{}
			<< ltn::inst::Writex{i_var.address}
			<< ltn::inst::Writex{from_var.address}
			<< ltn::inst::Writex{to_var.address};

		// Condition
		buf
			<< ltn::inst::Label{begin}
			<< ltn::inst::Readx{to_var.address}
			<< ltn::inst::Readx{from_var.address}
			<< ltn::inst::Readx{i_var.address}
			<< ltn::inst::Between{}
			<< ltn::inst::Ifelse{end};

		// body
		buf << body.code;

		// Increments
		buf << ltn::inst::Readx{ i_var.address };
		if(auto & step = stmt.step) {
			buf
				<< compile_expression(*step, info, loop_scope).code
				<< ltn::inst::Add{};
		}
		else {
			buf << ltn::inst::Inc{};
		}
		buf << ltn::inst::Writex{ i_var.address };

		// End of loop
		buf
			<< ltn::inst::Jump{ begin }
			<< ltn::inst::Label{ end };

		return StmtCode{ buf, body.var_count + 3 };
	}
}