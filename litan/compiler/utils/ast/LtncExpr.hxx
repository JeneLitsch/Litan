#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncToken.hxx"
#include "LtncTypeId.hxx"
#include "LtncNamespace.hxx"
#include "LtncConstValue.hxx"
namespace ltn::c {

	struct Expr : public AstNode {
		Expr(const DebugInfo & debugInfo) : AstNode(debugInfo) {}
		
		virtual ~Expr() = default;
	};

	struct ExprLiteral : public Expr {
		using Value = std::variant<
			std::int64_t,
			double,
			std::string,
			bool,
			std::monostate>;

		ExprLiteral(const DebugInfo & debugInfo, const Value & value)
			: Expr(debugInfo), value(value) {}
		Value value;
	};

	
	// Varible access: foo.bar.x
	struct ExprVar : public Expr {
		ExprVar(
			const DebugInfo & debugInfo,
			const std::vector<VarId> & path)
			: Expr(debugInfo), path(path) {}

		ExprVar(
			const DebugInfo & debugInfo,
			const VarId & varId)
			: Expr(debugInfo), path({varId}) {}
		
		ExprVar(
			const DebugInfo & debugInfo,
			const std::string & name)
			: Expr(debugInfo), path({name}) {}
		
		virtual ~ExprVar() = default;
		
		std::vector<VarId> path;
	};

	// Unary operator: -x
	struct ExprUnary : public Expr {
		virtual ~ExprUnary() = default;
		ExprUnary(
			const DebugInfo & debugInfo,
			TokenType type,
			std::unique_ptr<Expr> r)
			: Expr(debugInfo), type(type), r(std::move(r)) {}

		TokenType type;
		std::unique_ptr<Expr> r;
	};

	// Binary operator: a + b
	struct ExprBinary : public Expr {
		virtual ~ExprBinary() = default;
		ExprBinary(
			const DebugInfo & debugInfo,
			TokenType type,
			std::unique_ptr<Expr> l,
			std::unique_ptr<Expr> r)
			: Expr(debugInfo), type(type), l(std::move(l)), r(std::move(r)) {}

		TokenType type;
		std::unique_ptr<Expr> l;
		std::unique_ptr<Expr> r;
	};

	// Call function: ->fx();
	struct ExprCall : public Expr {
		virtual ~ExprCall() = default;

		ExprCall(
			const DebugInfo & debugInfo,
			const std::string & name,
			const Namespace & ns,
			std::vector<std::unique_ptr<Expr>> paramExprs)
			: Expr(debugInfo), name(name), ns(ns), paramExprs(std::move(paramExprs)) {}

		ExprCall(
			const DebugInfo & debugInfo,
			const std::string & name,
			const Namespace & ns)
			: Expr(debugInfo), name(name), ns(ns) {}

		std::string name;
		Namespace ns;
		std::vector<std::unique_ptr<Expr>> paramExprs;
	};
}