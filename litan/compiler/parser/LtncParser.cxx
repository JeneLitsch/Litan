#include "LtncParser.hxx"
#include <iostream>
#include "LtncParserCall.hxx"
#include "LtncParserPrimary.hxx"

ltnc::Parser::Parser() {
	this->stmt.connect(this->block, this->ifelse, this->assign, this->expr, this->call);
	this->block.connect(this->stmt, this->declVar);
	this->assign.connect(this->expr);
	this->function.connect(this->block);
	this->ifelse.connect(this->stmt, this->expr);
	

	this->expr.connect(this->comparison);
	this->comparison.connect(this->term);
	this->term.connect(this->product);
	this->product.connect(this->primary);
	this->primary.connect(this->call);
	this->call.connect(this->expr);
}


std::shared_ptr<ltnc::Program> ltnc::Parser::parse(const std::vector<Token> & tokens) const {
	ParserPackage parsePkg(tokens);
	auto program = std::make_shared<Program>();
	while(!parsePkg.isAtEnd()) {
		if(parsePkg.match(TokenType::FNX)){
			auto stmt = this->function.eval(parsePkg);
			program->functions.push_back(stmt);
		}
		else if (auto typeDecl = declType.eval(parsePkg)) {
			program->types.push_back(*typeDecl);
		}
		else {
			throw std::runtime_error("Unknown declaration at: " + parsePkg.curr().string);
		}
	}
	return program;
}