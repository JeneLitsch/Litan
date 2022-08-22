#include "compile.hxx"


namespace ltn::c {
	ExprCode compile_decltype(const ast::DeclType & expr, CompilerInfo & info, Scope & scope) {
		const auto result = compile_expression(*expr.expression, info, scope);
		const auto type = result.deduced_type;
		const auto name = type::to_string(type);
		const auto bytes = std::vector<std::uint8_t>{std::begin(name), std::end(name)};

		InstructionBuffer buf;
		buf << inst::Newstruct{};
		
		buf << inst::Duplicate{};
		buf << inst::Newstr{bytes};
		buf << inst::Swap{};
		buf << inst::MemberWrite{info.member_table.get_id("name")};

		return {buf};
	}


	// compiles any expression
	ExprCode compile_expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		if(auto binary = as<ast::Binary>(expr)) {
			return compile_binary(*binary, info, scope);
		}
		if(auto unary = as<ast::Unary>(expr)) {
			return compile_unary(*unary, info, scope);
		}
		if(auto expr_ = as<ast::Integer>(expr)) {
			return compile_integer(*expr_);
		}
		if(auto expr_ = as<ast::Float>(expr)) {
			return compile_floating(*expr_);
		} 
		if(auto expr_ = as<ast::Bool>(expr)) {
			return compile_boolean(*expr_);
		}
		if(auto expr_ = as<ast::Char>(expr)) {
			return compile_character(*expr_);
		}
		if(auto expr_ = as<ast::Null>(expr)) {
			return compile_null(*expr_);
		} 
		if(auto expr_ = as<ast::String>(expr)) {
			return compile_string(*expr_);
		} 
		if(auto expr_ = as<ast::Array>(expr)) {
			return compile_array(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Call>(expr)) {
			return compile_call(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Var>(expr)) {
			return compile_read_variable(*expr_, info, scope);
		} 	
		if(auto expr_ = as<ast::Index>(expr)) {
			return compile_index(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::Lambda>(expr)) {
			return compile_lambda(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::FxPointer>(expr)) {
			return compile_fxPointer(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Member>(expr)) {
			return compile_read_member_access(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::GlobalVar>(expr)) {
			return compile_read_static(*expr_, info, scope);
		}		
		if(auto expr_ = as<ast::Iife>(expr)) {
			return compile_iife(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::DefinitionValue>(expr)) {
			return compile_read_static(*expr_, info, scope);
		} 
		if(auto ternary = as<ast::Ternary>(expr)) {
			return compile_ternary(*ternary, info, scope);
		} 
		if(auto sw1tch = as<ast::ExprSwitch>(expr)) {
			return compile_expr_switch(*sw1tch, info, scope);
		} 
		if(auto invoke = as<ast::Invokation>(expr)) {
			return compile_invokation(*invoke, info, scope);
		}
		if(auto invoke = as<ast::DeclType>(expr)) {
			return compile_decltype(*invoke, info, scope);
		}
		throw CompilerError{"Unknown Expression"};
	}



	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}
}