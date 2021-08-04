#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
namespace ltnc {

	struct Expr;
	struct ExprVar;
	struct DeclVar;

	struct Stmt : public AstNode {
		Stmt(const DebugInfo & debugInfo) : AstNode(debugInfo) {}
		virtual ~Stmt() = default;
	};

	struct StmtReturn : public Stmt {
		StmtReturn(
			const DebugInfo & debugInfo,
			std::shared_ptr<Expr> expr)
			: Stmt(debugInfo), expr(expr) {}
		virtual ~StmtReturn() = default;
		std::shared_ptr<Expr> expr;
	};

	struct StmtExpr : public Stmt {
		StmtExpr(
			const DebugInfo & debugInfo,
			std::shared_ptr<Expr> expr)
			: Stmt(debugInfo), expr(expr) {}
		virtual ~StmtExpr() = default;
		std::shared_ptr<Expr> expr;
	};

	struct StmtAssign : public Stmt {
		StmtAssign(
			const DebugInfo & debugInfo,
			const std::shared_ptr<ExprVar> & var,
			std::shared_ptr<Expr> expr)
			: Stmt(debugInfo), var(var), expr(expr) {}
		virtual ~StmtAssign() = default;
		std::shared_ptr<ExprVar> var;
		std::shared_ptr<Expr> expr;
	};

	struct StmtPrint : public Stmt {
		StmtPrint(
			const DebugInfo & debugInfo,
			std::shared_ptr<Expr> expr)
			: Stmt(debugInfo), expr(expr) {}
		virtual ~StmtPrint() = default;
		std::shared_ptr<Expr> expr; 
	};

	struct StmtBlock : public Stmt {
		StmtBlock(const DebugInfo & debugInfo) : Stmt(debugInfo) {}

		virtual ~StmtBlock() = default;
		
		std::vector<std::shared_ptr<Stmt>> statements;
		std::vector<std::shared_ptr<DeclVar>> declarations;
	};

	struct StmtFor : public Stmt {
		StmtFor(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		virtual ~StmtFor() = default;
		std::string name = ""; 
		std::shared_ptr<Expr> exprFrom = nullptr; 
		std::shared_ptr<Expr> exprTo = nullptr; 
		std::shared_ptr<Stmt> stmt = nullptr;
	};

	struct StmtRepeat : public Stmt {
		StmtRepeat(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		virtual ~StmtRepeat() = default;
		std::shared_ptr<Expr> expr = nullptr; 
		std::shared_ptr<Stmt> stmt = nullptr;
	};

	struct StmtWhile : public Stmt {
		StmtWhile(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		virtual ~StmtWhile() = default;
		std::shared_ptr<Expr> expr = nullptr; 
		std::shared_ptr<Stmt> stmt = nullptr;
	};


	struct StmtIf : public Stmt {
		StmtIf(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		std::shared_ptr<Expr> condition; 
		std::shared_ptr<Stmt> stmtIf; 
		std::shared_ptr<Stmt> stmtElse;
		virtual ~StmtIf() = default;
	};

	struct StmtAsm : public Stmt {
		StmtAsm(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		std::vector<std::string> instructions;
		virtual ~StmtAsm() = default;
	};

}