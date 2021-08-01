#include "LtncParserFunctions.hxx"

bool mameSpace(ltnc::ParserPackage & parsePkg, ltnc::Program & program) {
	if(parsePkg.match(ltnc::TokenType::NAMESPACE)) {
		if(parsePkg.match(ltnc::TokenType::IDENTIFIER)) {
			parsePkg.ns.push(parsePkg.prev().string);
			// std::cout << parsePkg.ns.str() << std::endl;
			if(parsePkg.match(ltnc::TokenType::L_BRACE)) {
				while(!parsePkg.match(ltnc::TokenType::R_BRACE)) {
					ltnc::parse::declaration(parsePkg, program);
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

void ltnc::parse::declaration(ParserPackage & parsePkg, Program & program) {
	if(auto function = declareFunction(parsePkg)){
		program.functions.push_back(function);
	}
	else if (auto typeDecl = declareType(parsePkg)) {
		program.types.push_back(*typeDecl);
	}
	else if (auto structDecl = declareStruct(parsePkg)) {
		program.structs.push_back(*structDecl);
	}
	else if(::mameSpace(parsePkg, program)) {
 	}
	else {
		throw parsePkg.error("Unknown declaration at: " + parsePkg.curr().string);
	}
}
