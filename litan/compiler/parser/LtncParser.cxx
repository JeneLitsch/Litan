#include "LtncParser.hxx"
#include <iostream>
#include "LtncParserCall.hxx"
#include "LtncParserPrimary.hxx"

ltnc::Parser::Parser()
:	stmt(this->block, this->ifelse, this->assign, this->expr, this->call),
	block(this->stmt, this->declVar),
	assign(this->expr, this->var),
	function(this->block),
	ifelse(this->stmt, this->expr),
	declStruct(this->declVar),
	param(this->expr),
	expr(this->comparison, this->newstruct, this->delstruct),
	newstruct(this->param),
	delstruct(this->var),
	comparison(this->term),
	term(this->product), 
	product(this->unary),
	unary(this->primary),
	primary(this->call, this->var, this->expr),
	call(this->param),
	declVar(this->expr) {}


std::shared_ptr<ltnc::Program> ltnc::Parser::parse(const std::vector<Token> & tokens) const {
	ParserPackage parsePkg(tokens);
	auto program = std::make_shared<Program>();
	while(!parsePkg.isAtEnd()) {
		if(auto function = this->function.eval(parsePkg)){
			program->functions.push_back(function);
		}
		else if (auto typeDecl = this->declType.eval(parsePkg)) {
			program->types.push_back(*typeDecl);
		}
		else if (auto structDecl = this->declStruct.eval(parsePkg)) {
			program->structs.push_back(*structDecl);
		}
		else {
			throw std::runtime_error("Unknown declaration at: " + parsePkg.curr().string);
		}
	}
	return program;
}