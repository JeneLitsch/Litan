#include "LtncParserIfElse.hxx"

void ltnc::ParserIfElse::connect(const ParserNode<Stmt> & stmt, const ParserNode<Expr> & expr) {
	this->expr = &expr;
	this->stmt = &stmt;
}

std::shared_ptr<ltnc::Stmt> ltnc::ParserIfElse::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::IF)) {
		std::shared_ptr<Expr> condition;
		std::shared_ptr<Stmt> stmtIf;
		std::shared_ptr<Stmt> stmtElse;
		if(parsePkg.match(TokenType::L_PAREN)) {
			condition = this->expr->eval(parsePkg);
			if(parsePkg.match(TokenType::R_PAREN)) {
				stmtIf = this->stmt->eval(parsePkg);
				if(parsePkg.match(TokenType::ELSE)) {
					stmtElse = this->stmt->eval(parsePkg);
				}
			}
		}
		if(!expr || !stmtIf) {
			throw std::runtime_error("Invalid if-else");
		}
		auto ifElse = std::make_shared<StmtIf>();
		ifElse->stmtIf = stmtIf;
		ifElse->stmtElse = stmtElse;
		ifElse->condition = condition;
		return ifElse;
	}
	return nullptr;
}
