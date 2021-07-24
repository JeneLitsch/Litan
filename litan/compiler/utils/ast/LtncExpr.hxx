#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "LtncToken.hxx"
#include "LtncTypeId.hxx"
#include "LtncNamespace.hxx"
namespace ltnc {

	struct Expr {
		virtual ~Expr() = default;
	};

	// Int literal: 42
	struct ExprIntLiteral : public Expr {
		virtual ~ExprIntLiteral() = default;
		ExprIntLiteral(std::int64_t number): number(number) {}
		std::int64_t number;
	};

	// Flt literal: 42.0
	struct ExprFltLiteral : public Expr {
		virtual ~ExprFltLiteral() = default;
		ExprFltLiteral(double number): number(number) {}
		double number;
	};

	// Str literal: "hello world!"
	struct ExprStrLiteral : public Expr {
		virtual ~ExprStrLiteral() = default;
		ExprStrLiteral(std::string string): string(string) {}
		std::string string;
	};
	
	// Varible access: foo.bar.x
	struct ExprVar : public Expr {
		virtual ~ExprVar() = default;
		ExprVar(const std::string & name): path({name}) {}
		std::vector<std::string> path;
	};

	// Unary operator: -x
	struct ExprUnary : public Expr {
		virtual ~ExprUnary() = default;
		ExprUnary(
			TokenType type,
			const std::shared_ptr<Expr> & r)
			: type(type), r(r) {}

		TokenType type;
		std::shared_ptr<Expr> r;
	};

	// Binary operator: a + b
	struct ExprBinary : public Expr {
		virtual ~ExprBinary() = default;
		ExprBinary(
			TokenType type,
			const std::shared_ptr<Expr> & l,
			const std::shared_ptr<Expr> & r)
			: type(type), l(l), r(r) {}

		TokenType type;
		std::shared_ptr<Expr> l;
		std::shared_ptr<Expr> r;
	};

	// Call function: ->fx();
	struct ExprCall : public Expr {
		virtual ~ExprCall() = default;

		ExprCall(const std::string & name, const Namespace & ns, const std::vector<std::shared_ptr<Expr>> & paramExprs)
			: name(name), ns(ns), paramExprs(paramExprs) {}

		ExprCall(const std::string & name, const Namespace & ns)
			: name(name), ns(ns), paramExprs({}) {}

		std::string name;
		Namespace ns;
		std::vector<std::shared_ptr<Expr>> paramExprs;
	};

	// New operator: new Foo()
	struct ExprNew : public Expr {
		virtual ~ExprNew() = default;

		ExprNew(const TypeId & typeId, const std::vector<std::shared_ptr<Expr>> & paramExprs)
			: typeId(typeId), paramExprs(paramExprs) {}
		
		TypeId typeId;
		std::vector<std::shared_ptr<Expr>> paramExprs;
	};

	// New operator: new Foo()
	struct ExprDel : public Expr {
		virtual ~ExprDel() = default;
		ExprDel(const std::shared_ptr<ExprVar> & exprVar): exprVar(exprVar) {}
		std::shared_ptr<ExprVar> exprVar;
	};
}