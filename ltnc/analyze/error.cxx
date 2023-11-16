#include "error.hxx"

namespace ltn::c {
	CompilerError undefined_function(
		const std::string_view & name,
		const SourceLocation & location) {
				
		std::stringstream ss;
		ss << "Function " << name << " is not defined";
		return CompilerError { ss.str(), location };
	}



	CompilerError undefined_function(const ast::expr::Var & node) {
		return undefined_function(node.name, location(node));
	}



	CompilerError undefined_function(const ast::expr::FxPointer & node) {
		return undefined_function(node.name, location(node));
	}



	CompilerError undefined_template(const std::string_view & name, const SourceLocation & location) {
		std::stringstream ss;
		ss << "Template " << name << " is not defined";
		return CompilerError { ss.str(), location };
	}



	CompilerError const_call_violation(const ast::Node & node) {
		return CompilerError {
			"Cannot call non-const function from a const functions",
			ast::location(node)
		};
	}



	CompilerError private_call_violation(const ast::Node & node) {
		return CompilerError {
			"Function is not visible in current scope",
			ast::location(node)
		};
	}



	CompilerError const_assign_violation(const ast::Node & node) {
		return CompilerError{
			"Cannot modify or reassign variable in const function",
			location(node)
		};
	}



	CompilerError undefined_variable(const ast::expr::Var & var) {
		return CompilerError {
			"Undefined variable " + var.namespaze.to_string() + var.name,
			location(var)
		};
	}



	CompilerError redefined_variable(
		const std::string & name,
		const SourceLocation & location) {
		
		return CompilerError{
			"Redefintion of variable " + name,
			location
		};
	}



	CompilerError undefined_global(const ast::decl::Static & global) {
		std::ostringstream oss;
		oss
			<< "Undefined global variable "
			<< global.namespaze.to_string() << global.name;

		return CompilerError { oss.str(), location(global) };
	}




	CompilerError cannot_unpack_tuple(const ast::Node & node) {
		return CompilerError {
			"Cannot unpack tuple element",
			location(node)
		};
	}



	CompilerError left_side_not_assignable(const ast::Node & node) {
		return CompilerError {
			"Left side is not assignable",
			location(node)
		};
	}
}