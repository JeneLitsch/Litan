#include "compile.hxx"


namespace ltn::c {
	
	InstructionBuffer compile_expr(
		const sst::DeclType & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto result = compile_expression(*expr.expression, info, scope);
		const auto type = expr.type;
		const auto name = type::to_string(type);

		InstructionBuffer buf;
		buf << inst::newstruct();
		
		buf << inst::duplicate();
		buf << inst::newstr(name);
		buf << inst::swap();
		buf << inst::member_write(info.member_table.get_id("name"));

		return {buf};
	}



	// compiles any expression
	InstructionBuffer compile_expression(
		const sst::Expression & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		return sst::visit_expression(expr, [&](const auto & e) {
			return compile_expr(e, info, scope);
		});
	}
}