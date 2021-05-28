#include "Assembler.hxx"
#include <sstream>
#include <iostream>

// interate over code to find and save markers with their jump addresses
void ltn::Assembler::searchMarkers(const std::vector<TokenPackage> & tokenPackages){
	std::size_t cmdNr = 0;
	for(const TokenPackage & pkg : tokenPackages){		
		if(pkg.inst == "") {}
		if(pkg.inst == "//") {}
		else if(pkg.inst == "->") {
			// + 1 because of goto MAIN
			this->markers[pkg.args[0]] = cmdNr + 1;
		}
		else{
			cmdNr++;
		}
	}
}
void ltn::Assembler::registerAlias(const std::string & alias, IExtension::Slot slot, std::uint8_t funct){
	this->pseudoAssembler.registerAlias(alias, slot, funct);
}

// assemble code
std::vector<std::uint64_t> ltn::Assembler::assemble(const std::vector<TokenPackage> & tokens){
	this->markers.clear();
	this->instructions.clear();
	
	
	std::size_t lineNr = 1;
	
	std::vector<TokenPackage> tokenPackages = pseudoAssembler.process(tokens, includeDirectories);

	this->searchMarkers(tokenPackages);
	if(!this->markers.contains("MAIN")){
		throw std::runtime_error("MAIN is not defined");
	}
	this->assembleLine(TokenPackage("<automatic>", "goto", {"MAIN"}));
	for(const TokenPackage & pkg : tokenPackages){
		try{
			this->assembleLine(pkg);
		}	
		catch(std::runtime_error error) {
			throw std::runtime_error(
				"Error in line:" + std::to_string(lineNr) + " | " + pkg.line + "\n" + error.what());
		}
		lineNr++;
	}
	return this->instructions;
}

void ltn::Assembler::setIncludeDirectories(const std::vector<std::string> & includeDirectories){
	this->includeDirectories = includeDirectories;
}

void ltn::Assembler::assembleLine(const TokenPackage & pkg){
	if(pkg.inst == "") return;
	if(pkg.args.size() == 0){
		if(pkg.inst == "exit") return this->cFormat(InstCode::EXIT); 
		if(pkg.inst == "suspend") return this->cFormat(InstCode::SUSPEND); 
		if(pkg.inst == "error") return this->cFormat(InstCode::ERROR); 
		if(pkg.inst == "scrap") return this->cFormat(InstCode::SCRAP); 
		if(pkg.inst == "clear") return this->cFormat(InstCode::CLEAR); 
		if(pkg.inst == "print") return this->cFormat(InstCode::PRINT);
		if(pkg.inst == "fetch") return this->cFormat(InstCode::FETCH);
		if(pkg.inst == "copy") return this->cFormat(InstCode::COPY);
		if(pkg.inst == "size") return this->cFormat(InstCode::SIZE);
		if(pkg.inst == "init") return this->cFormat(InstCode::INIT);

		if(pkg.inst == "addi") return this->cFormat(InstCode::ADDI);
		if(pkg.inst == "subi") return this->cFormat(InstCode::SUBI);
		if(pkg.inst == "mlti") return this->cFormat(InstCode::MLTI);
		if(pkg.inst == "divi") return this->cFormat(InstCode::DIVI);
		if(pkg.inst == "powi") return this->cFormat(InstCode::POWI);
		if(pkg.inst == "modi") return this->cFormat(InstCode::MODI);
		if(pkg.inst == "inc") return this->cFormat(InstCode::INC);
		if(pkg.inst == "dec") return this->cFormat(InstCode::DEC);

		if(pkg.inst == "addf") return this->cFormat(InstCode::ADDF);
		if(pkg.inst == "subf") return this->cFormat(InstCode::SUBF);
		if(pkg.inst == "mltf") return this->cFormat(InstCode::MLTF);
		if(pkg.inst == "divf") return this->cFormat(InstCode::DIVF);
		if(pkg.inst == "powf") return this->cFormat(InstCode::POWF);
		if(pkg.inst == "modf") return this->cFormat(InstCode::MODF);
		
		if(pkg.inst == "bitor") return this->cFormat(InstCode::BITOR);
		if(pkg.inst == "bitand") return this->cFormat(InstCode::BITAND);
		if(pkg.inst == "bitxor") return this->cFormat(InstCode::BITXOR);

		if(pkg.inst == "logor") return this->cFormat(InstCode::LOGOR);
		if(pkg.inst == "logand") return this->cFormat(InstCode::LOGAND);
		if(pkg.inst == "logxor") return this->cFormat(InstCode::LOGXOR);

		if(pkg.inst == "eqli") return this->cFormat(InstCode::EQLI);
		if(pkg.inst == "smli") return this->cFormat(InstCode::SMLI);
		if(pkg.inst == "bgri") return this->cFormat(InstCode::BGRI);

		if(pkg.inst == "eqlf") return this->cFormat(InstCode::EQLF);
		if(pkg.inst == "smlf") return this->cFormat(InstCode::SMLF);
		if(pkg.inst == "bgrf") return this->cFormat(InstCode::BGRF);

		if(pkg.inst == "casti") return this->cFormat(InstCode::CASTI);
		if(pkg.inst == "castf") return this->cFormat(InstCode::CASTF);

		if(pkg.inst == "return") return this->cFormat(InstCode::RETURN);
		if(pkg.inst == "ifnx") return this->cFormat(InstCode::IFSK);

		if(pkg.inst == "spshi") return this->cFormat(InstCode::SPSHI);
		if(pkg.inst == "spshf") return this->cFormat(InstCode::SPSHF);

		if(pkg.inst == "load") return this->cFormat(InstCode::LOAD); 
		if(pkg.inst == "store") return this->cFormat(InstCode::STORE); 
		

		if(pkg.inst == "array::new") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::NEW));  
		if(pkg.inst == "array::del") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::DEL));  
		if(pkg.inst == "array::add") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::ADD));  
		if(pkg.inst == "array::pop") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::POP));  
		if(pkg.inst == "array::set") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::SET));  
		if(pkg.inst == "array::get") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::GET));  
		if(pkg.inst == "array::clr") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::CLR));  
		if(pkg.inst == "array::len") return this->fFormat(InstCode::ARRAY, static_cast<std::uint8_t>(ArrayFunct::LEN));  

		if(pkg.inst == "loop::inf") return this->fFormat(InstCode::LOOP, static_cast<std::uint8_t>(LoopFunct::INF));  
		if(pkg.inst == "loop::range") return this->fFormat(InstCode::LOOP, static_cast<std::uint8_t>(LoopFunct::RANGE));

		if(pkg.inst == "loop::cont") return this->fFormat(InstCode::LOOP, static_cast<std::uint8_t>(LoopFunct::CONT));  
		if(pkg.inst == "loop::stop") return this->fFormat(InstCode::LOOP, static_cast<std::uint8_t>(LoopFunct::STOP));

		if(pkg.inst == "loop::idx") return this->fFormat(InstCode::LOOP, static_cast<std::uint8_t>(LoopFunct::IDX));  
	}
	if(pkg.args.size() == 1){
		
		if(pkg.inst == "ext::0") return this->fFormat(InstCode::EXT0, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::1") return this->fFormat(InstCode::EXT1, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::2") return this->fFormat(InstCode::EXT2, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::3") return this->fFormat(InstCode::EXT3, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::4") return this->fFormat(InstCode::EXT4, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::5") return this->fFormat(InstCode::EXT5, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::6") return this->fFormat(InstCode::EXT6, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  
		if(pkg.inst == "ext::7") return this->fFormat(InstCode::EXT7, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));  

		if(pkg.inst == "call") return this->jFormat(InstCode::CALL, pkg.args[0]);  
		if(pkg.inst == "goto") return this->jFormat(InstCode::GOTO, pkg.args[0]);  

		if(pkg.inst == "newl") return this->vFormat(InstCode::NEWL, toInt32(pkg.args[0])); 
		if(pkg.inst == "newu") return this->vFormat(InstCode::NEWU, toInt32(pkg.args[0])); 
		if(pkg.inst == "->") return;

		if(pkg.inst == "print") return this->sFormat(InstCode::PRINT, static_cast<std::uint8_t>(toInt32(pkg.args[0])), 0, 0);
	}
	if(pkg.inst == "//") return;
	throw std::runtime_error("No signature matches: " + pkg.inst);
}

std::uint32_t ltn::Assembler::toInt32(const std::string & str){
	if(str.substr(0,2) == "0x"){
		return static_cast<std::uint32_t>(std::stoull(str.substr(2), nullptr, 16));
	}
	if(str.substr(0,2) == "0b"){
		return static_cast<std::uint32_t>(std::stoull(str.substr(2), nullptr, 2));
	}
	return static_cast<std::uint32_t>(std::stoull(str, nullptr, 10));
}

std::uint64_t ltn::Assembler::toInt64(const std::string & str){
	if(str.substr(0,2) == "0x"){
		return static_cast<std::uint64_t>(std::stoull(str.substr(2), nullptr, 16));
	}
	if(str.substr(0,2) == "0b"){
		return static_cast<std::uint64_t>(std::stoull(str.substr(2), nullptr, 2));
	}
	return static_cast<std::uint64_t>(std::stoull(str, nullptr, 10));
}

void ltn::Assembler::cFormat(InstCode code){
	std::uint64_t inst = 0;
	// opcode
	inst |= static_cast<std::uint8_t>(code);
	this->instructions.push_back(inst);
}

void ltn::Assembler::fFormat(InstCode code, std::uint8_t funct){
	std::uint64_t inst = 0;
	// opcode
	inst |= static_cast<std::uint8_t>(code);
	// 8-bit arg function code
	inst |= static_cast<std::uint64_t>(funct) << 8;
	this->instructions.push_back(inst);
}

void ltn::Assembler::vFormat(InstCode code, std::uint32_t val){
	std::uint64_t inst = 0;
	// opcode
	inst |= static_cast<std::uint8_t>(code);
	// 32bit parameter
	inst |= static_cast<std::uint64_t>(val) << 32;
	this->instructions.push_back(inst);
}
void ltn::Assembler::jFormat(InstCode code, const std::string & destination){
	std::uint64_t addr = 0;
	if(this->markers.contains(destination)){
		addr = this->markers.at(destination);
	}
	else {
		addr = this->toInt64(destination);
	}
	std::uint64_t inst = 0;
	// opcode
	inst |= static_cast<std::uint8_t>(code);
	// 56 address
	inst |= addr << 8;
	this->instructions.push_back(inst);
}

void ltn::Assembler::sFormat(InstCode code, std::uint8_t arg8, std::uint16_t arg16, std::uint32_t arg32){
	std::uint64_t inst = 0;
	// opcode
	inst |= static_cast<std::uint8_t>(code);
	// 8-bit arg
	inst |= static_cast<std::uint64_t>(arg8) << 8;
	// 16-bit arg
	inst |= static_cast<std::uint64_t>(arg16) << 16;
	// 32-bit arg
	inst |= static_cast<std::uint64_t>(arg32) << 32;
	this->instructions.push_back(inst);
}
