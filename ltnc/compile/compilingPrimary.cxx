#include "compiling.hxx"
#include <string_view>
namespace ltn::c::compile {
	namespace {
		CompilerError undefinedFunction(
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


		// compiles bool literal
		ExprCode character(const ast::Char & expr) {
			return ExprCode{ inst::newc(expr.value) };
		}

		// compiles string literal
		ExprCode string(const ast::String & expr) {
			std::stringstream ss;
			ss << inst::newstr << std::hex;
			std::string_view str = expr.value;
			while(str.size() >= 8) {
				ss << inst::char_8(str);		
			}
			while(str.size() >= 4) {
				ss << inst::char_4(str);
			}
			while(!str.empty()) {
				ss << inst::ch4r(str.front());
				str.remove_prefix(1);
			}
			return ExprCode{ ss.str() };
		}

		// compiles array literal
		ExprCode array(const ast::Array & array, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			ss << inst::newarr;
			for(const auto & elem : array.initElements) {
				ss << expression(*elem, info, scope).code;
				ss << inst::elem;
			}
			return ExprCode{ ss.str() };
		}



		// compiles function call fx(...)
		ExprCode callFx(const ast::Call & call, CompilerInfo & info, Scope & scope) {
			// resolve function
			const auto fx = info.fxTable.resolve(
				call.name,
				scope.getNamespace(),
				call.nameSpace,
				call.parameters.size());
			
			if(!fx) {
				throw undefinedFunction(call.name, call);
			}
			std::stringstream ss;
			for(const auto & param : call.parameters) {
				const auto paramCode = compile::expression(*param, info, scope);
				ss << paramCode.code;
			}
			ss << inst::call(fx->id);
			return ExprCode{ ss.str() };
		}

		ExprCode fxPointer(
			const ast::FxPointer & ptr,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto fx = info.fxTable.resolve(
				ptr.name,
				scope.getNamespace(),
				ptr.nameSpace,
				ptr.placeholders);
			if(!fx) {
				throw undefinedFunction(ptr.name, ptr);
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
			ss << readVar(*access.var, info, scope).code;
			for(const auto & member : access.memberpath) {
				const auto id = info.memberTable.getId(member);
				ss << inst::member_read(id);
			}
			return ExprCode{ ss.str() };
		}
	}

	// compiles an variable read accessc
	ExprCode readVar(const ast::Var & expr, CompilerInfo &, Scope & scope) {
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
			return readVar(*expr_, info, scope);
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
		
		throw CompilerError{"Unknown primary expression", expr.location};
	}
}