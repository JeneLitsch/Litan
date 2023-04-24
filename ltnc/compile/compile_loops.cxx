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



	InstructionBuffer compile_stmt(const sst::ForEach & stmt) {
		InstructionBuffer buf;
		const auto label_end = make_jump_id("FOREACH_END");
		const auto label_top = make_jump_id("FOREACH_BODY");
		
		// Init
		buf << compile_expression(*stmt.expr);
		buf << inst::iter();

		// Condition
		buf << inst::label(label_top);
		buf << inst::for_next(label_end);
		
		// Body
		buf << inst::write_x(stmt.element_addr);
		buf << compile_statement(*stmt.body);
		buf << inst::jump(label_top);
		
		// End
		buf << inst::label(label_end);
		buf << inst::scrap();

		return buf;
	}
}