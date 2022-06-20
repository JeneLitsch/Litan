#include "compile.hxx"
namespace ltn::c::compile {
	namespace {
		CompilerError not_mutable(const SourceLocation & location) {
			return CompilerError{
				"Cannot modify non-mutable variable",
				location};
		}



		ExprCode read_ref_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto arr = expression(*expr.expression, info, scope);
			InstructionBuffer buf;
			buf << arr.code;
			return ExprCode{ buf };
		}



		ExprCode read_ref_member(const ast::Member & expr, CompilerInfo & info, Scope & scope) {
			InstructionBuffer buf;
			buf << expression(*expr.expr, info, scope).code;
			return ExprCode{ buf };
		}



		// compile assignable variable
		ExprCode read_ref(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(as<ast::Var>(expr)) {
				return {};
			}
			if(auto e = as<ast::Index>(expr)) {
				return read_ref_index(*e, info, scope);
			}
			if(auto e = as<ast::Member>(expr)) {
				return read_ref_member(*e, info, scope);
			}
			throw std::runtime_error{"Unknow assingable type"};
		}



		ExprCode write_var(const ast::Var & expr, CompilerInfo &, Scope & scope) {
			const auto var = scope.resolve(expr.name, expr.location);
			if(is_mutable(var)) {
				InstructionBuffer buf;
				buf << ltn::inst::Writex{var.address};
				return ExprCode{ buf };
			}
			else throw not_mutable(expr.location);
		}



		ExprCode write_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto idx = expression(*expr.index, info, scope);
			InstructionBuffer buf;
			buf << idx.code;
			buf << ltn::inst::AtWrite{};
			return ExprCode{ buf };
		}



		ExprCode write_member(const ast::Member & expr, CompilerInfo & info, Scope &) {
			InstructionBuffer buf;
			const auto id = info.member_table.get_id(expr.name);
			buf << ltn::inst::MemberWrite{ id };
			return ExprCode{ buf };
		}

		

		// compile assignable variable
		ExprCode write(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto e = as<ast::Var>(expr)) {
				return write_var(*e, info, scope);
			}
			if(auto e = as<ast::Index>(expr)) {
				return write_index(*e, info, scope);
			}
			if(auto e = as<ast::Member>(expr)) {
				return write_member(*e, info, scope);
			}
			throw std::runtime_error{"Unknow assingable type"};
		}


		ExprCode read_var(const ast::Var & expr, CompilerInfo &, Scope & scope) {
			const auto var = scope.resolve(expr.name, expr.location);
			InstructionBuffer buf;
			buf << ltn::inst::Readx{var.address};
			return ExprCode{ buf };
		}



		ExprCode read_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto idx = expression(*expr.index, info, scope);
			InstructionBuffer buf;
			buf << idx.code;
			buf << ltn::inst::At{};
			return ExprCode{ buf };
		}



		ExprCode read_member(const ast::Member & expr, CompilerInfo & info, Scope &) {
			InstructionBuffer buf;
			const auto id = info.member_table.get_id(expr.name);
			buf << ltn::inst::MemberRead{id};
			return ExprCode{ buf };
		}

		

		// compile assignable variable
		ExprCode read(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto e = as<ast::Var>(expr)) {
				return read_var(*e, info, scope);
			}
			if(auto e = as<ast::Index>(expr)) {
				return read_index(*e, info, scope);
			}
			if(auto e = as<ast::Member>(expr)) {
				return read_member(*e, info, scope);
			}
			throw std::runtime_error{"Unknow assingable type"};
		}
	}



	StmtCode assign(
		const ast::Assign & expr,
		CompilerInfo & info,
		Scope & scope) {
		guard_const(expr, scope);
		const auto l_prepare = compile::read_ref(*expr.l, info, scope);
		const auto l_write = compile::write(*expr.l, info, scope);
		const auto r = compile::expression(*expr.r, info, scope);
		InstructionBuffer buf;
		buf << r.code;
		buf << l_prepare.code;
		buf << l_write.code;
		return StmtCode{ buf, 0 };
	}



	// += -= *= /= %=
	StmtCode modify(
		const ast::Modify & expr,
		CompilerInfo & info,
		Scope & scope) {
		using MT = ast::Modify::Type;
		guard_const(expr, scope);
		const auto l_prepare = compile::read_ref(*expr.l, info, scope);
		const auto l_write = compile::write(*expr.l, info, scope);
		const auto l_read = compile::read(*expr.l, info, scope);
		const auto r = compile::expression(*expr.r, info, scope);
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

		buf << l_read.code;
		buf << r.code;
		buf << op;

		if(as<ast::Index>(*expr.l) || as<ast::Member>(*expr.l)) {
			buf << ltn::inst::Swap{};
		}

		buf << l_write.code;			
		return StmtCode{ buf, 1, true };
	}
}