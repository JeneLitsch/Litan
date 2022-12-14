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

	InstructionBuffer compile_stmt(const sst::While & stmt) {

		// outer scope of loop 
		// compile parts
		const auto condition = compile_expression(*stmt.condition);
		const auto body = compile_statement(*stmt.body);
		const auto name = make_jump_id("WHILE");
		const auto begin = jump_begin(name);
		const auto end = jump_end(name);

		// generate asm code
		InstructionBuffer buf;
		buf 
			<< inst::label(begin)
			<< condition
			<< inst::ifelse(end)
			<< body
			<< inst::jump(begin)
			<< inst::label(end);

		return buf;
	}



	InstructionBuffer compile_stmt(const sst::InfiniteLoop & stmt) {

		// compile parts
		const auto body = compile_statement(*stmt.body);
		const auto jump = make_jump_id("INFINETE_LOOP");

		// generate asm code
		InstructionBuffer buf;
		buf
			<< inst::label(jump)
			<< body
			<< inst::jump(jump);

		return buf;
	}



	InstructionBuffer compile_stmt(const sst::For & stmt) {
		
		// outer scope of loop 
		const auto var = compile_statement(*stmt.var);
		const auto from = compile_expression(*stmt.from);
		const auto to = compile_expression(*stmt.to);
		
		const auto begin = jump_begin(stmt.label);
		const auto end = jump_end(stmt.label);

		const auto i_var    = loop_scope.resolve(stmt.var->name);
		const auto from_var = loop_scope.insert(var_from(stmt.label));
		const auto to_var   = loop_scope.insert(var_to(stmt.label));

		const auto body = compile_statement(*stmt.body);
				
		InstructionBuffer buf;
		
		// Init
		buf
			<< to
			<< from
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
		buf << body;

		// Increments
		buf << inst::read_x(i_var->address);
		if(auto & step = stmt.step) {
			buf
				<< compile_expression(*step)
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

		return buf;
	}
}