#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "LtncToken.hxx"
namespace ltnc {
	struct Expr {
		virtual ~Expr() = default;
		
	};

	struct ExprIntLiteral : public Expr {
		virtual ~ExprIntLiteral() = default;
		ExprIntLiteral(std::int64_t number): number(number) {}
		std::int64_t number;
	};

	struct ExprFltLiteral : public Expr {
		virtual ~ExprFltLiteral() = default;
		ExprFltLiteral(double number): number(number) {}
		double number;
	};
	
	struct ExprVar : public Expr {
		virtual ~ExprVar() = default;
		ExprVar(const std::string & name): name(name) {}
		std::string name;
	};

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

	struct ExprCall : public Expr {
		virtual ~ExprCall() = default;
		ExprCall(const std::string & name, const std::vector<std::shared_ptr<Expr>> & paramExprs)
			: name(name), paramExprs(paramExprs) {}
		ExprCall(const std::string & name)
			: name(name), paramExprs({}) {}
		std::string name;
		std::vector<std::shared_ptr<Expr>> paramExprs;
	};
}