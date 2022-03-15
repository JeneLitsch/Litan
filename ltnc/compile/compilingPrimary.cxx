#include "compiling.hxx"
#include <string_view>
namespace ltn::c::compile {
	namespace {
		CompilerError undefined_function(
			const std::string_view & name,
			const ast::Node & node) {
			std::stringstream ss;
			ss << "Function " << name << " is not defined";
			return CompilerError { ss.str(), node.location };
		}

		// Literals

		// compiles int literal
		ExprCode integer(const ast::Integer & expr) {
			return ExprCode{inst::newi(expr.value) };
		}

		// compiles float literal
		ExprCode floating(const ast::Float & expr) {
			return ExprCode{ inst::newf(expr.value) };
		}

		// compiles bool literal
		ExprCode boolean(const ast::Bool & expr) {
			const auto inst = (expr.value ? inst::truE : inst::falsE);
			return ExprCode{ std::string(inst) };
		}

		// compiles null literal
		ExprCode null(const ast::Null &) {
			return ExprCode{ std::string(inst::null) };
		}


		// compiles bool literal
		ExprCode character(const ast::Char & expr) {
			return ExprCode{ inst::newc(expr.value) };
		}

		// compiles string literal
		ExprCode string(const ast::String & expr) {
			return ExprCode{ inst::newstr(expr.value) };
		}

		// compiles array literal
		ExprCode array(const ast::Array & array, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			for(const auto & elem : array.elements) {
				ss << expression(*elem, info, scope).code;
			}
			ss << inst::newarr(array.elements.size());
			return ExprCode{ ss.str() };
		}



		// compiles function call fx(...)
		ExprCode callFx(const ast::Call & call, CompilerInfo & info, Scope & scope) {
			// resolve function
			const auto fx = info.fx_table.resolve(
				call.name,
				scope.get_namespace(),
				call.namespaze,
				call.parameters.size());
			
			if(!fx) {
				throw undefined_function(call.name, call);
			}
			std::stringstream ss;
			for(const auto & param : call.parameters) {
				ss << compile::expression(*param, info, scope).code;
			}
			ss << inst::call(fx->id);
			return ExprCode{ ss.str() };
		}

		ExprCode fxPointer(
			const ast::FxPointer & ptr,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto fx = info.fx_table.resolve(
				ptr.name,
				scope.get_namespace(),
				ptr.namespaze,
				ptr.placeholders);
			if(!fx) {
				throw undefined_function(ptr.name, ptr);
			}
			std::stringstream ss;
			ss << inst::newfx(fx->id, ptr.placeholders);
			return ExprCode{ss.str() };
		}

		// compiles index read operation
		ExprCode index(const ast::Index & index, CompilerInfo & info, Scope & scope) {
			const auto arr = expression(*index.expression, info, scope);
			const auto idx = expression(*index.index, info, scope);
			std::stringstream ss;
			ss	<< arr.code
				<< idx.code
				<< inst::at;
			return ExprCode{ss.str() };
		}

		ExprCode readMemberAccess(
			const ast::MemberAccess & access,
			CompilerInfo & info,
			Scope & scope) {
			std::stringstream ss;
			ss << read_variable(*access.var, info, scope).code;
			for(const auto & member : access.memberpath) {
				const auto id = info.memberTable.get_id(member);
				ss << inst::member_read(id);
			}
			return ExprCode{ ss.str() };
		}

		ExprCode iife(const ast::Iife & iife, CompilerInfo & info, Scope & outer_scope) {
			const auto jumpmark = make_jump_id("IIFE", info);
			Scope inner_scope{&outer_scope};
			inner_scope.set_return(jumpmark);
			std::ostringstream ss;
			ss << compile::statement(*iife.stmt, info, inner_scope).code;
			ss << inst::null;
			ss << inst::jumpmark(jumpmark);
			return {ss.str()};
		}
	}

	// compiles an variable read accessc
	ExprCode read_variable(const ast::Var & expr, CompilerInfo &, Scope & scope) {
		const auto var = scope.resolve(expr.name, expr.location);
		std::stringstream ss;
		ss << inst::read_x(var.address);
		return ExprCode{ ss.str() };
	}

	




	// compiles Primary expression
	ExprCode primary(const ast::Primary & expr, CompilerInfo & info, Scope & scope) {
		if(auto expr_ = as<ast::Integer>(expr)) {
			return integer(*expr_);
		} 
		if(auto expr_ = as<ast::Float>(expr)) {
			return floating(*expr_);
		} 
		if(auto expr_ = as<ast::Bool>(expr)) {
			return boolean(*expr_);
		}
		if(auto expr_ = as<ast::Char>(expr)) {
			return character(*expr_);
		}
		if(auto expr_ = as<ast::Null>(expr)) {
			return null(*expr_);
		} 
		if(auto expr_ = as<ast::String>(expr)) {
			return string(*expr_);
		} 
		if(auto expr_ = as<ast::Array>(expr)) {
			return array(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Call>(expr)) {
			return callFx(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Var>(expr)) {
			return read_variable(*expr_, info, scope);
		} 	
		if(auto expr_ = as<ast::Index>(expr)) {
			return index(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::Lambda>(expr)) {
			return lambda(*expr_, info, scope);
		}	
		if(auto expr_ = as<ast::FxPointer>(expr)) {
			return fxPointer(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::MemberAccess>(expr)) {
			return readMemberAccess(*expr_, info, scope);
		}		
		if(auto expr_ = as<ast::Iife>(expr)) {
			return compile::iife(*expr_, info, scope);
		} 
		throw CompilerError{"Unknown primary expression", expr.location};
	}
}