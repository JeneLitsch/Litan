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
				throw ltnc::error::expectedBraceL(parsePkg);
			}
		}
		else {
			throw ltnc::error::unnamedNamespace(parsePkg);
		}
	}
	return false;
}

void ltnc::parse::declaration(ParserPackage & parsePkg, Program & program) {
	if(auto function = declareFunction(parsePkg)){
		program.functions.push_back(std::move(function));
	}
	else if (auto typeDecl = declareType(parsePkg)) {
		program.types.push_back(std::move(typeDecl));
	}
	else if (auto structDecl = declareStruct(parsePkg)) {
		program.structs.push_back(std::move(structDecl));
	}
	else if(::mameSpace(parsePkg, program)) {
 	}
	else {
		throw error::expectedDeclaration(parsePkg);
	}
}
