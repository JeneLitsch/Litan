#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncToken.hxx"
#include "LtncTypeId.hxx"
#include "LtncNamespace.hxx"
namespace ltnc {

	struct Expr : public AstNode {
		Expr(const DebugInfo & debugInfo) : AstNode(debugInfo) {}
		
		virtual ~Expr() = default;
	};

	// Int literal: 42
	struct ExprIntLiteral : public Expr {
		ExprIntLiteral(const DebugInfo & debugInfo, std::int64_t number)
			: Expr(debugInfo), number(number) {}
		
		virtual ~ExprIntLiteral() = default;
		
		std::int64_t number;
	};

	// Flt literal: 42.0
	struct ExprFltLiteral : public Expr {
		ExprFltLiteral(const DebugInfo & debugInfo, double number)
			: Expr(debugInfo), number(number) {}
		
		virtual ~ExprFltLiteral() = default;
		
		double number;
	};

	struct ExprNul : public Expr {
		virtual ~ExprNul() = default;
		ExprNul(const DebugInfo & debugInfo)
			: Expr(debugInfo) {}
	};

	struct ExprBool : public Expr {
		virtual ~ExprBool() = default;
		ExprBool(bool value, const DebugInfo & debugInfo)
			: Expr(debugInfo), value(value) {}
		bool value;
	};

	// Str literal: "hello world!"
	struct ExprStrLiteral : public Expr {
		virtual ~ExprStrLiteral() = default;
		ExprStrLiteral(const DebugInfo & debugInfo, std::string string)
			: Expr(debugInfo), string(string) {}
		std::string string;
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
			const std::shared_ptr<Expr> & r)
			: Expr(debugInfo), type(type), r(r) {}

		TokenType type;
		std::shared_ptr<Expr> r;
	};

	// Binary operator: a + b
	struct ExprBinary : public Expr {
		virtual ~ExprBinary() = default;
		ExprBinary(
			const DebugInfo & debugInfo,
			TokenType type,
			const std::shared_ptr<Expr> & l,
			const std::shared_ptr<Expr> & r)
			: Expr(debugInfo), type(type), l(l), r(r) {}

		TokenType type;
		std::shared_ptr<Expr> l;
		std::shared_ptr<Expr> r;
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