#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "conversion.hxx"

namespace ltn::c {
	namespace {

		// compile assignable variable
		ExprCode compile_read_ref(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto var = as<ast::Var>(expr)) {
				const auto & local = scope.resolve(var->name, var->location);
				return {
					.code = {},
					.deduced_type = local.type,
				};
			}
			
			if(auto index = as<ast::Index>(expr)) {
				const auto arr = compile_expression(*index->expression, info, scope);
				InstructionBuffer buf;
				buf << arr.code;
				return ExprCode{ 
					.code = buf,
					.deduced_type = arr.deduced_type,
				};
			}
			
			if(auto e = as<ast::Member>(expr)) {
				InstructionBuffer buf;
				buf << compile_expression(*e->expr, info, scope).code;
				return ExprCode{ buf };
			}

			if(as<ast::GlobalVar>(expr)) {
				return {};
			}
			
			throw std::runtime_error{"Unknow assingable type"};
		}



		InstructionBuffer compile_write(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto e = as<ast::Var>(expr)) {
				const auto var = scope.resolve(e->name, expr.location);
				InstructionBuffer buf;
				buf << ltn::inst::Writex{var.address};
				return buf;
			}
			
			if(auto e = as<ast::Index>(expr)) {
				const auto idx = compile_expression(*e->index, info, scope);
				InstructionBuffer buf;
				buf << idx.code;
				buf << ltn::inst::AtWrite{};
				return buf;
			}
			
			if(auto e = as<ast::Member>(expr)) {
				InstructionBuffer buf;
				const auto id = info.member_table.get_id(e->name);
				buf << ltn::inst::MemberWrite{ id };
				return buf;
			}
			
			if(auto global = as<ast::GlobalVar>(expr)) {
				return compile_write_static(*global, info, scope).code;
			}

			throw std::runtime_error{"Unknown assingable type"};
		}

		

		// compile assignable variable
		InstructionBuffer compile_read(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto e = as<ast::Var>(expr)) {
				const auto var = scope.resolve(e->name, e->location);
				InstructionBuffer buf;
				buf << ltn::inst::Readx{var.address};
				return buf;
			}
			
			if(auto e = as<ast::Index>(expr)) {
				const auto idx = compile_expression(*e->index, info, scope);
				InstructionBuffer buf;
				buf << idx.code;
				buf << ltn::inst::At{};
				return buf;
			}

			if(auto e = as<ast::Member>(expr)) {
				InstructionBuffer buf;
				const auto id = info.member_table.get_id(e->name);
				buf << ltn::inst::MemberRead{id};
				return buf;
			}

			if(auto e = as<ast::GlobalVar>(expr)) {
				return compile_read_static(*e, info, scope).code;
			}

			throw std::runtime_error{"Unknown assingable type"};
		}
	}



	StmtCode compile_assign(
		const ast::Assign & expr,
		CompilerInfo & info,
		Scope & scope) {
		guard_const(expr, scope);
		const auto l_prepare = compile_read_ref(*expr.l, info, scope);
		const auto l_write = compile_write(*expr.l, info, scope);
		const auto r = compile_expression(*expr.r, info, scope);

		InstructionBuffer buf;
		buf << r.code;
		buf << l_prepare.code;
		buf << conversion_on_assign(
			r.deduced_type,
			l_prepare.deduced_type,
			expr.location
		);
		buf << l_write;
		return StmtCode{ 
			.code = buf,
			.var_count = 0,
			.direct_allocation = false,
		};
	}



	StmtCode compile_modify(
		const ast::Modify & expr,
		CompilerInfo & info,
		Scope & scope) {
		using MT = ast::Modify::Type;
		guard_const(expr, scope);
		const auto l_prepare = compile_read_ref(*expr.l, info, scope);
		const auto l_write = compile_write(*expr.l, info, scope);
		const auto l_read = compile_read(*expr.l, info, scope);
		const auto r = compile_expression(*expr.r, info, scope);
		const auto op = [&] () -> ltn::inst::Instruction {
			switch (expr.type) {
			case MT::ADD:     return ltn::inst::Add{};
			case MT::SUB:     return ltn::inst::Sub{};
			case MT::MLT:     return ltn::inst::Mlt{};
			case MT::DIV:     return ltn::inst::Div{};
			case MT::MOD:     return ltn::inst::Mod{};
			case MT::POW:     return ltn::inst::Pow{};
			case MT::SHIFT_L: return ltn::inst::ShiftL{};
			case MT::SHIFT_R: return ltn::inst::ShiftR{};
			case MT::BITAND:  return ltn::inst::Bitand{};
			case MT::BITOR:   return ltn::inst::Bitor{};
			case MT::BITXOR:  return ltn::inst::Bitxor{};
			}
			throw CompilerError{
				"Unknow modify operator",
				expr.location};
		}();
		InstructionBuffer buf;
		buf << l_prepare.code;
		
		if(as<ast::Index>(*expr.l) || as<ast::Member>(*expr.l)) {
			buf << ltn::inst::Duplicate{};
		}

		buf << l_read;
		buf << r.code;
		buf << op;

		if(as<ast::Index>(*expr.l) || as<ast::Member>(*expr.l)) {
			buf << ltn::inst::Swap{};
		}

		buf << conversion_on_modify(
			r.deduced_type,
			l_prepare.deduced_type,
			expr.location
		);
		buf << l_write;			
		return StmtCode{
			.code = buf,
			.var_count = 1,
			.direct_allocation = true,
		};
	}



	namespace {
		ExprCode compile_new_variable_right(
			const ast::NewVar & new_var,
			CompilerInfo & info,
			Scope & scope) {
			
			if(new_var.expression) {
				return compile_expression(*new_var.expression, info, scope);
			}
			else {
				InstructionBuffer buf;
				buf << ltn::inst::Null{};
				return ExprCode {
					.code = buf,
					.deduced_type = type::Null{}, 
				};
			}
		}
	}



	StmtCode compile_new_variable(const ast::NewVar & new_var, CompilerInfo & info, Scope & scope) {
		const auto var = scope.insert(new_var.name, new_var.location, new_var.type);
		const auto r = compile_new_variable_right(new_var, info, scope);
		
		InstructionBuffer buf;
		buf << r.code;
		buf << conversion_on_assign(
			r.deduced_type,
			new_var.type,
			new_var.location
		);
		buf << ltn::inst::Writex{var.address};
		return { 
			.code = buf,
			.var_count = 0,
			.direct_allocation = true,
		};
	}
}