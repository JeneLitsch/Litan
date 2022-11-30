#include "compile.hxx"


namespace ltn::c {
	
	ExprResult compile_expr(const ast::DeclType & expr, CompilerInfo & info, Scope & scope) {
		const auto result = compile_expression(*expr.expression, info, scope);
		const auto type = result.deduced_type;
		const auto name = type::to_string(type);
		const auto bytes = std::vector<std::uint8_t>{std::begin(name), std::end(name)};

		InstructionBuffer buf;
		buf << inst::newstruct();
		
		buf << inst::duplicate();
		buf << inst::newstr(bytes);
		buf << inst::swap();
		buf << inst::member_write(info.member_table.get_id("name"));

		return {buf};
	}



	// compiles any expression
	ExprResult compile_expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		return ast::visit_expression(expr, [&](const auto & e) {
			return compile_expr(e, info, scope);
		});
	}



	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}
}