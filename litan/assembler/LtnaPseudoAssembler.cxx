#include "LtnaPseudoAssembler.hxx"
#include "LtnaAssemblerParser.hxx"
#include "LtnFloat.hxx"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <filesystem>

std::vector<ltna::TokenPackage> ltna::PseudoAssembler::process(const std::vector<TokenPackage> & tokensPackages) {
	this->newPkgs.clear();
	bool ok = true;
	std::size_t lineNr = 1;
	for(const TokenPackage & pkg : tokensPackages){ 
		try {
			this->processPkg(pkg);
		}	
		catch(std::runtime_error error) {
			std::cout << "Error in line:" + std::to_string(lineNr) << " | " << pkg.line << std::endl;
			std::cout << error.what() << std::endl;
			ok = false;
		}
		lineNr++;
	}
	if(ok) {
		return this->newPkgs;
	}
	else {
		return { TokenPackage("Preprocessor Error", "error", {})};
	}
}

void ltna::PseudoAssembler::registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct) {
	this->aliases[alias] = { slot, funct };
}

void ltna::PseudoAssembler::processPkg(const TokenPackage & pkg) {
	if (pkg.args.size() == 1) {
		if(pkg.inst == "newi") {
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

		if(pkg.inst == "newf") {
			try {
				double valueD = std::stod(pkg.args[0]);
				std::uint64_t valueI = ltn::Float::doubleToUint(valueD);
				long valueL = (valueI >> 0) & 0xffffffff;
				long valueU = (valueI >> 32) & 0xffffffff;
				this->processPkg(TokenPackage(pkg.line, "newl" , {std::to_string(valueL)}));
				if(valueU != 0){
					this->processPkg(TokenPackage(pkg.line, "newu" , {std::to_string(valueU)}));
					this->processPkg(TokenPackage(pkg.line, "bitor", {}));
				}
			}
			catch(...) {
				throw std::runtime_error("Invalid floating point number: \"" + pkg.args[0] + "\"");
			}
			return;
		}
	}

	// resolve aliases
	if(this->aliases.contains(pkg.inst)) {
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