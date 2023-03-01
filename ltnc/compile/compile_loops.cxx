#include "compile.hxx"

namespace ltn::c {
	namespace {
		std::string jump_begin(const std::string & name) {
			return name + "_BEGIN";
		}

		std::string jump_end(const std::string & name) {
			return name + "_END";
		}
	}

	InstructionBuffer compile_stmt(const sst::While & stmt) {
		const auto condition = compile_expression(*stmt.condition);
		const auto body = compile_statement(*stmt.body);
		const auto name = make_jump_id("WHILE");
		const auto begin = jump_begin(name);
		const auto end = jump_end(name);

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
		const auto body = compile_statement(*stmt.body);
		const auto jump = make_jump_id("INFINETE_LOOP");

		InstructionBuffer buf;
		buf
			<< inst::label(jump)
			<< body
			<< inst::jump(jump);
		return buf;
	}



	InstructionBuffer compile_stmt(const sst::For & loop) {
		
		// outer scope of loop 
		const auto from = compile_expression(*loop.from);
		const auto to = compile_expression(*loop.to);
		
		const auto begin = jump_begin(loop.label);
		const auto end = jump_end(loop.label);

		const auto from_var = loop.index_addr + 1;
		const auto to_var   = loop.index_addr + 2;

		const auto body = compile_statement(*loop.body);
				
		InstructionBuffer buf;
		
		// Init
		buf
			<< to
			<< from
			<< inst::duplicate()
			<< inst::write_x(loop.index_addr)
			<< inst::write_x(from_var)
			<< inst::write_x(to_var);

		// Condition
		buf
			<< inst::label(begin)
			<< inst::read_x(to_var)
			<< inst::read_x(from_var)
			<< inst::read_x(loop.index_addr)
			<< inst::between()
			<< inst::ifelse(end);

		// body
		buf
			<< body;

		// Increments
		buf 
			<< inst::read_x(loop.index_addr)
			<< compile_expression(*loop.step)
			<< inst::add()
			<< inst::write_x(loop.index_addr);

		// End of loop
		buf
			<< inst::jump(begin)
			<< inst::label(end);

		return buf;
	}



	InstructionBuffer compile_stmt(const sst::ForEach & stmt) {
		InstructionBuffer buf;
		const auto label_end = make_jump_id("FOREACH_HEAD");
		const auto label_top = make_jump_id("FOREACH_BODY");
		
		// Init
		buf << compile_expression(*stmt.expr);
		buf << inst::write_x(stmt.container_addr);
		buf << inst::newi(0);
		buf << inst::write_x(stmt.iterator_addr);

		// Condition
		buf << inst::label(label_top);
		buf << inst::read_x(stmt.iterator_addr);
		buf << inst::read_x(stmt.container_addr) << inst::size();
		buf << inst::lt();
		buf << inst::ifelse(label_end);
		
		// Load element
		buf << inst::read_x(stmt.container_addr);
		buf << inst::read_x(stmt.iterator_addr);
		buf << inst::at();
		buf << inst::write_x(stmt.element_addr);
		
		// Body
		buf << compile_statement(*stmt.body);
		
		// Next
		buf << inst::read_x(stmt.iterator_addr);
		buf << inst::inc();
		buf << inst::write_x(stmt.iterator_addr);
		buf << inst::jump(label_top);
		
		// End
		buf << inst::label(label_end);

		return buf;
	}
}