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
		this->parseDecl(parsePkg, *program);
	}
	return program;
}

bool ltnc::Parser::parseNamespace(ParserPackage & parsePkg, Program & program) const {
	if(parsePkg.match(TokenType::NAMESPACE)) {
		if(parsePkg.match(TokenType::IDENTIFIER)) {
			parsePkg.ns.push(parsePkg.prev().string);
			// std::cout << parsePkg.ns.str() << std::endl;
			if(parsePkg.match(TokenType::L_BRACE)) {
				while(!parsePkg.match(TokenType::R_BRACE)) {
					parseDecl(parsePkg, program);
				}
				parsePkg.ns.pop();
				return true;
			}
			else {
				throw parsePkg.error("Expected { after namespace declaration");
			}
		}
		else {
			throw parsePkg.error("Expected name after keyword namespace");
		}
	}
	return false;
}

void ltnc::Parser::parseDecl(ParserPackage & parsePkg, Program & program) const {
	if(auto function = this->function.eval(parsePkg)){
		program.functions.push_back(function);
	}
	else if (auto typeDecl = this->declType.eval(parsePkg)) {
		program.types.push_back(*typeDecl);
	}
	else if (auto structDecl = this->declStruct.eval(parsePkg)) {
		program.structs.push_back(*structDecl);
	}
	else if(this->parseNamespace(parsePkg, program)) {
 	}
	else {
		throw std::runtime_error("Unknown declaration at: " + parsePkg.curr().string);
	}
}
