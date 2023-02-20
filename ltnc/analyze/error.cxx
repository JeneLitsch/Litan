#include "error.hxx"

namespace ltn::c {
	CompilerError undefined_function(
		const std::string_view & name,
		const ast::Node & node) {
			
		std::stringstream ss;
		ss << "Function " << name << " is not defined";
		return CompilerError { ss.str(), location(node) };
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



	CompilerError undefined_variable(const ast::Var & var) {
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



	CompilerError undefined_type(const type::Other & type) {
		return CompilerError{
			"Undeclared type " + type.type_name 
		};
	}



	CompilerError undefined_global(const ast::GlobalVar & global) {
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



	CompilerError cannot_assign(
		const SourceLocation & location,
		const type::Type & from,
		const type::Type & to) {
		std::ostringstream oss;
		oss << "Cannot assign " << from << " to "<< to;
		return CompilerError{oss.str(), location};
	}



	CompilerError cannot_pass(
		const ArgumentLocation & location,
		const type::Type & from,
		const type::Type & to) {
		std::ostringstream oss;
		oss << "Cannot pass " << from << " as " << to << " for argument " << location.index+1;
		return CompilerError{oss.str(), location.source_location};
	}



	CompilerError cannot_return(
		const SourceLocation & location,
		const type::Type & from,
		const type::Type & to) {
		std::ostringstream oss;
		oss << "Cannot return " << from << " as "<< to;
		return CompilerError{oss.str(), location};
	}



	CompilerError cannot_cast(
		const SourceLocation & location,
		const type::Type & from,
		const type::Type & to) {
		std::ostringstream oss;
		oss << "Cannot cast " << from << " to " << to;
		return CompilerError{oss.str(), location};
	}



	CompilerError cannot_default_init(
		const type::Type & type,
		const SourceLocation & location) {
		std::ostringstream oss;
		oss << "Cannot default initialize type " << type;
		return CompilerError { oss.str(), location };
	}



	CompilerError invalid_operands(const ast::Node & node) {
		return CompilerError {
			"Invalid operands for expr",
			location(node)
		};
	}



	CompilerError invalid_operands(
		const ast::Binary & node,
		const type::Type & l,
		const type::Type & r) {
		
		std::ostringstream oss;
		oss 
			<< "Invalid operands ("
			<< l << " and " << r
			<< ") for binary expr";

		return CompilerError { oss.str(), location(node) };
	}



	CompilerError invalid_operands(const ast::Unary & node, const type::Type & type) {
		std::ostringstream oss;
		oss 
			<< "Invalid operands ("
			<< type
			<< ") for unary expr";

		return CompilerError { oss.str(), location(node) };
	}
}