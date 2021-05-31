#include "PseudoAssembler.hxx"
#include "LtnFloat.hxx"
#include "AssemblerParser.hxx"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <filesystem>
std::vector<ltn::TokenPackage> ltn::PseudoAssembler::process(const std::vector<TokenPackage> & tokensPackages){
	this->newPkgs.clear();
	bool ok = true;
	std::size_t lineNr = 1;
	for(const TokenPackage & pkg : tokensPackages){
		try{
			this->processPkg(pkg);
		}	
		catch(std::runtime_error error) {
			std::cout << "Error in line:" + std::to_string(lineNr) << " | " << pkg.line << std::endl;
			std::cout << error.what() << std::endl;
			ok = false;
		}
		lineNr++;
	}
	if(ok){
		return this->newPkgs;
	}
	else{
		return { TokenPackage("Preprocessor Error", "error", {})};
	}
}

void ltn::PseudoAssembler::registerAlias(const std::string & alias, Slot slot, std::uint8_t funct){
	this->aliases[alias] = { slot, funct };
}

void ltn::PseudoAssembler::includeFile(const std::string & path){
	if(this->includeGuard.contains(path)) return;
	this->includeGuard.insert(path);
	AssemblerParser parser;
	std::ifstream file(path);
	std::string source((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();
	for(const TokenPackage & extPkg : parser.parse(source)) {
		this->processPkg(extPkg);
	}
}

void ltn::PseudoAssembler::processPkg(const TokenPackage & pkg){
	if(pkg.args.size() == 0){
		
		if(pkg.inst == "bitnot"){
			this->processPkg(TokenPackage(pkg.line, "newl" , {"0xffffffff"}));
			this->processPkg(TokenPackage(pkg.line, "newu" , {"0xffffffff"}));
			this->processPkg(TokenPackage(pkg.line, "bitor" , {}));
			this->processPkg(TokenPackage(pkg.line, "bitxor" , {}));
			return;
		}

		if(pkg.inst == "lognot"){
			this->processPkg(TokenPackage(pkg.line, "newl" , {"1"}));
			this->processPkg(TokenPackage(pkg.line, "logxor" , {}));
			return;
		}

		if(pkg.inst == "ifnot"){
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			this->processPkg(TokenPackage(pkg.line, "ifnx" , {}));
			return;
		}

		if(pkg.inst == "smleqli"){
			this->processPkg(TokenPackage(pkg.line, "bgri" , {}));
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			return;
		}

		if(pkg.inst == "bgreqli"){
			this->processPkg(TokenPackage(pkg.line, "smli" , {}));
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			return;
		}

		if(pkg.inst == "uneqli"){
			this->processPkg(TokenPackage(pkg.line, "eqli" , {}));
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			return;
		}

		if(pkg.inst == "smleqlf"){
			this->processPkg(TokenPackage(pkg.line, "bgrf" , {}));
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			return;
		}

		if(pkg.inst == "bgreqlf"){
			this->processPkg(TokenPackage(pkg.line, "smlf" , {}));
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			return;
		}

		if(pkg.inst == "uneqlf"){
			this->processPkg(TokenPackage(pkg.line, "eqli" , {}));
			this->processPkg(TokenPackage(pkg.line, "lognot" , {}));
			return;
		}

		if(pkg.inst == "memcopyptr"){
			this->processPkg(TokenPackage(pkg.line, "load" , {}));
			this->processPkg(TokenPackage(pkg.line, "store" , {}));
			return;
		}

		if(pkg.inst == "zero"){
			this->processPkg(TokenPackage(pkg.line, "newl" , {"0"}));
			return;
		}
	}
	
	if (pkg.args.size() == 1) {
		if(pkg.inst == "newi"){
			long value = std::stoll(pkg.args[0]);
			long valueL = (value >> 0) & 0xffffffff;
			long valueU = (value >> 32) & 0xffffffff;
			this->processPkg(TokenPackage(pkg.line, "newl" , {std::to_string(valueL)}));

			// optimize for small positive values
			if(valueU != 0){
				this->processPkg(TokenPackage(pkg.line, "newu" , {std::to_string(valueU)}));
				this->processPkg(TokenPackage(pkg.line, "bitor", {}));
			}
			return;
		}

		if(pkg.inst == "newf"){
			try {
				double valueD = std::stod(pkg.args[0]);
				std::uint64_t valueI = ltn::Float::doubleToUint(valueD);
				std::cout << valueD << std::endl;	
				long valueL = (valueI >> 0) & 0xffffffff;
				long valueU = (valueI >> 32) & 0xffffffff;
				this->processPkg(TokenPackage(pkg.line, "newl" , {std::to_string(valueL)}));
				this->processPkg(TokenPackage(pkg.line, "newu" , {std::to_string(valueU)}));
				this->processPkg(TokenPackage(pkg.line, "bitor", {}));

			}
			catch(...) {
				throw std::runtime_error("Invalid floating point number: \"" + pkg.args[0] + "\"");
			}
			return;
		}

		if(pkg.inst == "load"){
			this->processPkg(TokenPackage(pkg.line, "newl" , {pkg.args[0]}));
			this->processPkg(TokenPackage(pkg.line, "load", {}));
			return;
		}

		if(pkg.inst == "store"){
			this->processPkg(TokenPackage(pkg.line, "newl" , {pkg.args[0]}));
			this->processPkg(TokenPackage(pkg.line, "store", {}));
			return;
		}

		if(pkg.inst == "loop::times"){
			this->processPkg(TokenPackage(pkg.line, "newl", {"1"}));
			this->processPkg(TokenPackage(pkg.line, "newl", {pkg.args[0]}));
			this->processPkg(TokenPackage(pkg.line, "loop::range", {}));
			return;
		}
		

	}

	if (pkg.args.size() == 2){

		if(pkg.inst == "memcopy"){
			this->processPkg(TokenPackage(pkg.line, "load" , {pkg.args[0]}));
			this->processPkg(TokenPackage(pkg.line, "store", {pkg.args[1]}));
			return;
		}

		if(pkg.inst == "loop::range"){
			this->processPkg(TokenPackage(pkg.line, "newi", {pkg.args[0]}));
			this->processPkg(TokenPackage(pkg.line, "newi", {pkg.args[1]}));
			this->processPkg(TokenPackage(pkg.line, "loop::range", {}));
			return;
		}


	}

	// allows the caling of ext::x commands with args
	if(pkg.args.size() > 1){
		// multiple new(x) and load operations in one line
		if(pkg.inst.substr(0,5) == "ext::"){
			this->processPkg(TokenPackage(pkg.line, "push", std::vector(pkg.args.begin()+1, pkg.args.end())));
			this->processPkg(TokenPackage(pkg.line, pkg.inst, {pkg.args[0]}));
			return;
		}
	}


	// resolve aliases
	if(this->aliases.contains(pkg.inst)){
		auto cmd = aliases.at(pkg.inst);
		auto args = pkg.args;
		// funct, arg1, arg2...
		args.insert(args.begin(), std::to_string(cmd.second));
		long extensionSlot = static_cast<long>(cmd.first);
		this->processPkg(TokenPackage(pkg.line, "ext::" + std::to_string(extensionSlot), args));
		return;
	}


	this->newPkgs.push_back(pkg);
}