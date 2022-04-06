#include "compile.hxx"
namespace ltn::c::compile {
	namespace {
		CompilerError not_mutable(const SourceLocation & location) {
			return CompilerError{
				"Cannot modify non-mutable variable",
				location};
		}



		ExprCode prepare_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto arr = expression(*expr.expression, info, scope);
			std::stringstream ss;
			ss << arr.code;
			return ExprCode{ss.str() };
		}



		ExprCode prepare_member(const ast::Member & expr, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			ss << expression(*expr.expr, info, scope).code;
			return ExprCode{ss.str() };
		}



		// compile assignable variable
		ExprCode prepare(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
			if(auto e = as<ast::Var>(expr)) {
				return {};
			}
			if(auto e = as<ast::Index>(expr)) {
				return prepare_index(*e, info, scope);
			}
			if(auto e = as<ast::Member>(expr)) {
				return prepare_member(*e, info, scope);
			}
			throw std::runtime_error{"Unknow assingable type"};
		}



		ExprCode write_var(const ast::Var & expr, CompilerInfo & info, Scope & scope) {
			const auto var = scope.resolve(expr.name, expr.location);
			if(is_mutable(var)) {
				std::stringstream ss;
				ss << inst::write_x(var.address);
				return ExprCode{ss.str() };
			}
			else throw not_mutable(expr.location);
		}



		ExprCode write_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto idx = expression(*expr.index, info, scope);
			std::ostringstream ss;
			ss << idx.code;
			ss << inst::at_write;
			return ExprCode{ss.str() };
		}



		ExprCode write_member(const ast::Member & expr, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			const auto id = info.member_table.get_id(expr.name);
			ss << inst::member_write(id);
			return ExprCode{ss.str() };
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


		ExprCode read_var(const ast::Var & expr, CompilerInfo & info, Scope & scope) {
			const auto var = scope.resolve(expr.name, expr.location);
			std::stringstream ss;
			ss << inst::read_x(var.address);
			return ExprCode{ss.str() };
		}



		ExprCode read_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto idx = expression(*expr.index, info, scope);
			std::ostringstream ss;
			ss << idx.code;
			ss << inst::at;
			return ExprCode{ss.str() };
		}



		ExprCode read_member(const ast::Member & expr, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			const auto id = info.member_table.get_id(expr.name);
			ss << inst::member_read(id);
			return ExprCode{ss.str() };
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
		const auto l_prepare = compile::prepare(*expr.l, info, scope);
		const auto l_write = compile::write(*expr.l, info, scope);
		const auto r = compile::expression(*expr.r, info, scope);
		std::stringstream ss;
		ss << r.code;
		ss << l_prepare.code;
		ss << l_write.code;
		return StmtCode{ss.str(), 0};
	}



	// += -= *= /= %=
	StmtCode modify(
		const ast::Modify & expr,
		CompilerInfo & info,
		Scope & scope) {
		using MT = ast::Modify::Type;
		guard_const(expr, scope);
		const auto l_prepare = compile::prepare(*expr.l, info, scope);
		const auto l_write = compile::write(*expr.l, info, scope);
		const auto l_read = compile::read(*expr.l, info, scope);
		const auto r = compile::expression(*expr.r, info, scope);
		const auto op = [&] {
			switch (expr.type) {
			case MT::ADD:     return inst::add;
			case MT::SUB:     return inst::sub;
			case MT::MLT:     return inst::mlt;
			case MT::DIV:     return inst::div;
			case MT::MOD:     return inst::mod;
			case MT::SHIFT_L: return inst::shift_l;
			case MT::SHIFT_R: return inst::shift_r;
			}
			throw CompilerError{
				"Unknow modify operator",
				expr.location};
		}();
		std::stringstream ss;
		ss << l_prepare.code;
		
		if(as<ast::Index>(*expr.l) || as<ast::Member>(*expr.l)) {
			ss << inst::duplicate;
		}

		ss << l_read.code;
		ss << r.code;
		ss << op;

		if(as<ast::Index>(*expr.l) || as<ast::Member>(*expr.l)) {
			ss << "swap\n";
		}

		ss << l_write.code;			
		return StmtCode{ss.str(), 1, true};
	}
}