#include "compile.hxx"


namespace ltn::c {
	
	ExprResult compile_decltype(const ast::DeclType & expr, CompilerInfo & info, Scope & scope) {
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



	struct ExprVisitor {
		ExprResult operator()(const ast::Lambda & e) {
			return compile_lambda(e, info, scope);
		}
		ExprResult operator()(const ast::DeclType & e) {
			return compile_decltype(e, info, scope);
		}
		ExprResult operator()(const ast::ExprSwitch & e) {
			return compile_expr_switch(e, info, scope);
		}
		ExprResult operator()(const ast::Ternary & e) {
			return compile_ternary(e, info, scope);
		}
		ExprResult operator()(const ast::Binary & e) {
			return compile_binary(e, info, scope);
		}
		ExprResult operator()(const ast::Unary & e) {
			return compile_unary(e, info, scope);
		}
		ExprResult operator()(const ast::Integer & e) {
			return compile_integer(e);
		}
		ExprResult operator()(const ast::Float & e) {
			return compile_floating(e);
		}
		ExprResult operator()(const ast::Bool & e) {
			return compile_boolean(e);
		}
		ExprResult operator()(const ast::Char & e) {
			return compile_character(e);
		}
		ExprResult operator()(const ast::Null & e) {
			return compile_null(e);
		}
		ExprResult operator()(const ast::String & e) {
			return compile_string(e);
		}
		ExprResult operator()(const ast::Array & e) {
			return compile_array(e, info, scope);
		}
		ExprResult operator()(const ast::Call & e) {
			return compile_call(e, info, scope);
		}
		ExprResult operator()(const ast::Index & e) {
			return compile_index(e, info, scope);
		}
		ExprResult operator()(const ast::FxPointer & e) {
			return compile_fxPointer(e, info, scope);
		}
		ExprResult operator()(const ast::Iife & e) {
			return compile_iife(e, info, scope);
		}
		ExprResult operator()(const ast::Var & e) {
			return compile_read_variable(e, info, scope);
		}
		ExprResult operator()(const ast::Member & e) {
			return compile_read_member_access(e, info, scope);
		}
		ExprResult operator()(const ast::GlobalVar & e) {
			return compile_read_global(e, info, scope);
		}
		ExprResult operator()(const ast::TypedUnary & e) {
			return compile_typed_unary(e, info, scope);
		}
		ExprResult operator()(const ast::Reflect & e) {
			return compile_reflect(e, info, scope);
		}
		CompilerInfo & info;
		Scope & scope;
	};



	// compiles any expression
	ExprResult compile_expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		return ast::visit_expression(expr, ExprVisitor{info, scope});
	}



	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}
}