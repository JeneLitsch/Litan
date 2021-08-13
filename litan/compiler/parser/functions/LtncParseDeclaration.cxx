#include "LtncParserFunctions.hxx"

bool mameSpace(ltn::c::ParserPackage & parsePkg, ltn::c::Program & program) {
	if(parsePkg.match(ltn::c::TokenType::NAMESPACE)) {
		if(parsePkg.match(ltn::c::TokenType::IDENTIFIER)) {
			parsePkg.ns.push(parsePkg.prev().string);
			// std::cout << parsePkg.ns.str() << std::endl;
			if(parsePkg.match(ltn::c::TokenType::L_BRACE)) {
				while(!parsePkg.match(ltn::c::TokenType::R_BRACE)) {
					ltn::c::parse::declaration(parsePkg, program);
				}
				parsePkg.ns.pop();
				return true;
			}
			else {
				throw ltn::c::error::expectedBraceL(parsePkg);
			}
		}
		else {
			throw ltn::c::error::unnamedNamespace(parsePkg);
		}
	}
	return false;
}

void ltn::c::parse::declaration(ParserPackage & parsePkg, Program & program) {
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
