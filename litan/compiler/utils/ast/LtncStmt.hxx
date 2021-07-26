#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncType.hxx"
#include "LtncVar.hxx"
namespace ltnc {

	struct Expr;
	struct ExprVar;
	struct DeclVar;

	struct Stmt {
		virtual ~Stmt() = default;
	};

	struct StmtReturn : public Stmt {
		StmtReturn(std::shared_ptr<Expr> expr)
			: expr(expr) {}
		virtual ~StmtReturn() = default;
		std::shared_ptr<Expr> expr;
	};

	struct StmtExpr : public Stmt {
		StmtExpr(std::shared_ptr<Expr> expr)
			: expr(expr) {}
		virtual ~StmtExpr() = default;
		std::shared_ptr<Expr> expr;
	};

	struct StmtAssign : public Stmt {
		StmtAssign(const std::shared_ptr<ExprVar> & var, std::shared_ptr<Expr> expr)
			: var(var), expr(expr) {}
		virtual ~StmtAssign() = default;
		std::shared_ptr<ExprVar> var;
		std::shared_ptr<Expr> expr;
	};

	struct StmtPrint : public Stmt {
		StmtPrint(std::shared_ptr<Expr> expr)
			: expr(expr) {}
		virtual ~StmtPrint() = default;
		std::shared_ptr<Expr> expr; 
	};

	struct StmtBlock : public Stmt {
		virtual ~StmtBlock() = default;
		std::vector<std::shared_ptr<Stmt>> statements;
		std::vector<std::shared_ptr<DeclVar>> declarations;
	};

	struct StmtFor : public Stmt {
		virtual ~StmtFor() = default;
		std::string name = ""; 
		std::shared_ptr<Expr> exprFrom = nullptr; 
		std::shared_ptr<Expr> exprTo = nullptr; 
		std::shared_ptr<Stmt> stmt = nullptr;
	};

	struct StmtRepeat : public Stmt {
		virtual ~StmtRepeat() = default;
		std::shared_ptr<Expr> expr = nullptr; 
		std::shared_ptr<Stmt> stmt = nullptr;
	};

	struct StmtWhile : public Stmt {
		virtual ~StmtWhile() = default;
		std::shared_ptr<Expr> expr = nullptr; 
		std::shared_ptr<Stmt> stmt = nullptr;
	};


	struct StmtIf : public Stmt {
		std::shared_ptr<Expr> condition; 
		std::shared_ptr<Stmt> stmtIf; 
		std::shared_ptr<Stmt> stmtElse;
		virtual ~StmtIf() = default;
	};

	struct StmtAsm : public Stmt {
		std::vector<std::string> instructions;
		virtual ~StmtAsm() = default;
	};

}