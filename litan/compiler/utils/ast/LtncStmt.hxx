#pragma once
#include <string>
#include <memory>
#include <vector>
#include "LtncAstNode.hxx"
#include "LtncType.hxx"
#include "LtncVar.hxx"
#include "LtncExpr.hxx"
namespace ltn::c {

	struct StmtVar;

	struct Stmt : public AstNode {
		Stmt(const DebugInfo & debugInfo) : AstNode(debugInfo) {}
		virtual ~Stmt() = default;
	};

	struct StmtReturn : public Stmt {
		StmtReturn(
			const DebugInfo & debugInfo,
			std::unique_ptr<Expr> expr)
			: Stmt(debugInfo), expr(std::move(expr)) {}
		virtual ~StmtReturn() = default;
		std::unique_ptr<Expr> expr;
	};

	struct StmtExpr : public Stmt {
		StmtExpr(
			const DebugInfo & debugInfo,
			std::unique_ptr<Expr> expr)
			: Stmt(debugInfo), expr(std::move(expr)) {}
		virtual ~StmtExpr() = default;
		std::unique_ptr<Expr> expr;
	};

	struct StmtAssign : public Stmt {
		StmtAssign(
			const DebugInfo & debugInfo,
			std::unique_ptr<ExprVar> var,
			std::unique_ptr<Expr> expr)
			: Stmt(debugInfo), var(std::move(var)), expr(std::move(expr)) {}
		virtual ~StmtAssign() = default;
		std::unique_ptr<ExprVar> var;
		std::unique_ptr<Expr> expr;
	};

	struct StmtPrint : public Stmt {
		StmtPrint(
			const DebugInfo & debugInfo,
			std::unique_ptr<Expr> expr)
			: Stmt(debugInfo), expr(std::move(expr)) {}
		virtual ~StmtPrint() = default;
		std::unique_ptr<Expr> expr; 
	};

	struct StmtBlock : public Stmt {
		StmtBlock(const DebugInfo & debugInfo) : Stmt(debugInfo) {}

		virtual ~StmtBlock() = default;
		
		std::vector<std::unique_ptr<Stmt>> statements;
	};

	struct StmtFor : public Stmt {
		StmtFor(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		virtual ~StmtFor() = default;
		std::string name = ""; 
		std::unique_ptr<Expr> exprFrom = nullptr; 
		std::unique_ptr<Expr> exprTo = nullptr; 
		std::unique_ptr<Stmt> stmt = nullptr;
	};

	struct StmtRepeat : public Stmt {
		StmtRepeat(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		virtual ~StmtRepeat() = default;
		std::unique_ptr<Expr> expr = nullptr; 
		std::unique_ptr<Stmt> stmt = nullptr;
	};

	struct StmtWhile : public Stmt {
		StmtWhile(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		virtual ~StmtWhile() = default;
		std::unique_ptr<Expr> expr = nullptr; 
		std::unique_ptr<Stmt> stmt = nullptr;
	};


	struct StmtIf : public Stmt {
		StmtIf(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		std::unique_ptr<Expr> condition; 
		std::unique_ptr<Stmt> stmtIf; 
		std::unique_ptr<Stmt> stmtElse;
		virtual ~StmtIf() = default;
	};

	struct StmtAsm : public Stmt {
		StmtAsm(const DebugInfo & debugInfo) : Stmt(debugInfo) {}
		std::vector<std::string> instructions;
		virtual ~StmtAsm() = default;
	};

	struct StmtVar : public Stmt {
		StmtVar(
			const DebugInfo & debugInfo,
			const VarId & varId,
			const TypeId & typeId)
		: 	Stmt(debugInfo),
			varId(varId),
			typeId(typeId) {}

		StmtVar(
			const DebugInfo & debugInfo,
			const VarId & varId,
			const TypeId & typeId,
			std::unique_ptr<Stmt> assign)
		: 	Stmt(debugInfo),
			varId(varId),
			typeId(typeId),
			assign(std::move(assign)) {}

		virtual ~StmtVar() = default;
		
		VarId varId;
		TypeId typeId;
		std::unique_ptr<Stmt> assign;
	};

}