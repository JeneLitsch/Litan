#include "Assembler.hxx"
#include <sstream>
#include <iostream>
#include <iomanip>
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
void ltn::Assembler::registerAlias(const std::string & alias, Slot slot, std::uint8_t funct){
	this->pseudoAssembler.registerAlias(alias, slot, funct);
}

// assemble code
std::vector<std::uint64_t> ltn::Assembler::assemble(const std::vector<TokenPackage> & tokens){
	this->markers.clear();
	this->instructions.clear();
	
	
	std::size_t lineNr = 1;
	
	std::vector<TokenPackage> tokenPackages = pseudoAssembler.process(tokens);

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


void ltn::Assembler::assembleLine(const TokenPackage & pkg){
	if(pkg.inst == "") return;
	if(pkg.args.size() == 0){
		if(pkg.inst == "exit") return this->cFormat(InstCode::EXIT);
		if(pkg.inst == "error") return this->cFormat(InstCode::ERROR);
		if(pkg.inst == "scrap") return this->cFormat(InstCode::SCRAP); 
		if(pkg.inst == "clear") return this->cFormat(InstCode::CLEAR); 
		if(pkg.inst == "copy") return this->cFormat(InstCode::COPY);
		if(pkg.inst == "size") return this->cFormat(InstCode::SIZE);
		if(pkg.inst == "init") return this->cFormat(InstCode::INIT);

		if(pkg.inst == "print::newline") return this->fFormat(InstCode::PRINT, ltn::OuputFormat::NEWLINE);
		if(pkg.inst == "print::int") return this->fFormat(InstCode::PRINT, ltn::OuputFormat::INT);
		if(pkg.inst == "print::uint") return this->fFormat(InstCode::PRINT, ltn::OuputFormat::UINT);
		if(pkg.inst == "print::float") return this->fFormat(InstCode::PRINT, ltn::OuputFormat::FLOAT);
		if(pkg.inst == "print::string") return this->fFormat(InstCode::PRINT, ltn::OuputFormat::STRING);

		if(pkg.inst == "addi") return this->cFormat(InstCode::ADDI);
		if(pkg.inst == "subi") return this->cFormat(InstCode::SUBI);
		if(pkg.inst == "mlti") return this->cFormat(InstCode::MLTI);
		if(pkg.inst == "divi") return this->cFormat(InstCode::DIVI);
		if(pkg.inst == "powi") return this->cFormat(InstCode::POWI);
		if(pkg.inst == "modi") return this->cFormat(InstCode::MODI);

		if(pkg.inst == "inc") return this->cFormat(InstCode::INCI);
		if(pkg.inst == "dec") return this->cFormat(InstCode::DECI);
		if(pkg.inst == "inci") return this->cFormat(InstCode::INCI);
		if(pkg.inst == "deci") return this->cFormat(InstCode::DECI);

		if(pkg.inst == "incf") std::runtime_error("Flaoting point incrementation not valid");
		if(pkg.inst == "decf") std::runtime_error("Flaoting point decrementation not valid");

		if(pkg.inst == "mnsi") return this->cFormat(InstCode::MNSI);
		if(pkg.inst == "mnsf") return this->cFormat(InstCode::MNSF);
		if(pkg.inst == "mini") return this->cFormat(InstCode::MINI);
		if(pkg.inst == "minf") return this->cFormat(InstCode::MINF);
		if(pkg.inst == "maxi") return this->cFormat(InstCode::MAXI);
		if(pkg.inst == "maxf") return this->cFormat(InstCode::MAXF);

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

		if(pkg.inst == "casti") return this->fFormat(InstCode::CASTI, 0);
		if(pkg.inst == "castf") return this->fFormat(InstCode::CASTF, 0);

		if(pkg.inst == "return") return this->cFormat(InstCode::RETURN);
		if(pkg.inst == "ifnx") return this->cFormat(InstCode::IFSK);

		if(pkg.inst == "spshi") return this->cFormat(InstCode::SPSHI);
		if(pkg.inst == "spshf") return this->cFormat(InstCode::SPSHF);

		if(pkg.inst == "load") return this->cFormat(InstCode::LOAD); 
		if(pkg.inst == "store") return this->cFormat(InstCode::STORE); 
		
		if(pkg.inst == "heap::allocate::array") return this->fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::ARRAY);  
		if(pkg.inst == "heap::allocate::stack") return this->fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::STACK);  
		if(pkg.inst == "heap::allocate::queue") return this->fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::QUEUE);  
		if(pkg.inst == "heap::allocate::deque") return this->fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::DEQUE);  
		if(pkg.inst == "heap::allocate::string") return this->fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::STRING);  
		if(pkg.inst == "heap::delete") return this->cFormat(InstCode::HEAP_DELETE);  
		if(pkg.inst == "heap::exist") return this->cFormat(InstCode::HEAP_EXIST);
		if(pkg.inst == "heap::istype::array") return this->fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::ARRAY);
		if(pkg.inst == "heap::istype::stack") return this->fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::STACK);
		if(pkg.inst == "heap::istype::queue") return this->fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::QUEUE);
		if(pkg.inst == "heap::istype::deque") return this->fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::DEQUE);
		if(pkg.inst == "heap::istype::string") return this->fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::STRING);
		if(pkg.inst == "heap::copy") return this->cFormat(InstCode::HEAP_COPY);

		if(pkg.inst == "array::set") return this->cFormat(InstCode::ARRAY_SET);  
		if(pkg.inst == "array::get") return this->cFormat(InstCode::ARRAY_GET);  
		if(pkg.inst == "array::clear") return this->cFormat(InstCode::ARRAY_CLEAR);  
		if(pkg.inst == "array::size") return this->cFormat(InstCode::ARRAY_SIZE);  
		if(pkg.inst == "array::empty") return this->cFormat(InstCode::ARRAY_EMPTY);  
		if(pkg.inst == "array::fill") return this->cFormat(InstCode::ARRAY_FILL);  
		if(pkg.inst == "array::resize") return this->cFormat(InstCode::ARRAY_RESIZE);  
		if(pkg.inst == "array::erase") return this->cFormat(InstCode::ARRAY_ERASE);  
		if(pkg.inst == "array::insert") return this->cFormat(InstCode::ARRAY_INSERT);  
		if(pkg.inst == "array::pushback") return this->cFormat(InstCode::ARRAY_PUSHB);  
		if(pkg.inst == "array::popback") return this->cFormat(InstCode::ARRAY_POPB);
		if(pkg.inst == "array::front") return this->cFormat(InstCode::ARRAY_FRONT);
		if(pkg.inst == "array::back") return this->cFormat(InstCode::ARRAY_BACK);

		if(pkg.inst == "stack::push") return this->cFormat(InstCode::STACK_PUSH);  
		if(pkg.inst == "stack::pop") return this->cFormat(InstCode::STACK_POP);  
		if(pkg.inst == "stack::top") return this->cFormat(InstCode::STACK_TOP);  
		if(pkg.inst == "stack::size") return this->cFormat(InstCode::STACK_SIZE);  
		if(pkg.inst == "stack::empty") return this->cFormat(InstCode::STACK_EMPTY);  
		if(pkg.inst == "stack::clear") return this->cFormat(InstCode::STACk_CLEAR);  

		if(pkg.inst == "queue::push") return this->cFormat(InstCode::QUEUE_PUSH);  
		if(pkg.inst == "queue::pop") return this->cFormat(InstCode::QUEUE_POP);  
		if(pkg.inst == "queue::front") return this->cFormat(InstCode::QUEUE_FRONT);  
		if(pkg.inst == "queue::size") return this->cFormat(InstCode::QUEUE_SIZE);  
		if(pkg.inst == "queue::empty") return this->cFormat(InstCode::QUEUE_EMPTY);  
		if(pkg.inst == "queue::clear") return this->cFormat(InstCode::QUEUE_CLEAR);  

		if(pkg.inst == "deque::pushf") return this->cFormat(InstCode::DEQUE_PUSHF);  
		if(pkg.inst == "deque::pushb") return this->cFormat(InstCode::DEQUE_PUSHB);  
		if(pkg.inst == "deque::popf") return this->cFormat(InstCode::DEQUE_POPF);  
		if(pkg.inst == "deque::popb") return this->cFormat(InstCode::DEQUE_POPB);  
		if(pkg.inst == "deque::front") return this->cFormat(InstCode::DEQUE_FRONT);  
		if(pkg.inst == "deque::back") return this->cFormat(InstCode::DEQUE_BACK);  
		if(pkg.inst == "deque::size") return this->cFormat(InstCode::DEQUE_SIZE);  
		if(pkg.inst == "deque::empty") return this->cFormat(InstCode::DEQUE_EMPTY);  
		if(pkg.inst == "deque::clear") return this->cFormat(InstCode::DEQUE_CLEAR);  

		if(pkg.inst == "string::add") return this->cFormat(InstCode::STRING_ADD);  

		if(pkg.inst == "loop::inf") return this->cFormat(InstCode::LOOP_INF);  
		if(pkg.inst == "loop::range") return this->cFormat(InstCode::LOOP_RANGE);
		if(pkg.inst == "loop::cont") return this->cFormat(InstCode::LOOP_CONT);  
		if(pkg.inst == "loop::stop") return this->cFormat(InstCode::LOOP_STOP);
		if(pkg.inst == "loop::idx") return this->cFormat(InstCode::LOOP_IDX);  
	}
	if(pkg.args.size() == 1){
		if(pkg.inst == "casti") return this->fFormat(InstCode::CASTI, static_cast<std::uint8_t>(this->toInt32(pkg.args[0])));
		
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
		if(pkg.inst == "stackalloc") return this->vFormat(InstCode::STACKALLOC, toInt32(pkg.args[0])); 
		if(pkg.inst == "->") return;
	}
	if(pkg.inst == "string::data") {
		std::uint64_t data = 0;
		std::string str = this->decodeString(pkg.args);
		std::size_t len = str.size();
		if(len > 6) {
			std::cout << ">> Warning: String data to long" << std::endl;
		}
		data |= std::uint8_t(len);
		for(std::size_t i = 0; i < len; i++) {
			char chr = str[i];
			data |= std::uint64_t(chr) << (i+1)*8;
		}
		return this->dFormat(InstCode::STRING_DATA, data); 
	}

	if(pkg.inst == "//") return;
	throw std::runtime_error("No signature matches: " + pkg.inst);
}

std::string ltn::Assembler::decodeString(const std::vector<std::string> & args) const {
	std::string encodedString;
	for(const std::string & arg : args) {
		encodedString += arg + " ";
	}
	encodedString.pop_back();
	if(encodedString.front() != '\'' || encodedString.back() != '\'') {
		throw std::runtime_error("String is not delimited");
	}
	encodedString.pop_back();
	encodedString.erase(encodedString.begin());

	std::vector<std::string> encodedChars;
	
	for(unsigned idx = 0; idx < encodedString.size(); idx++) {
		char chr = encodedString[idx];
		if(chr == '\\') {
			encodedChars.push_back(encodedString.substr(idx,2));
			idx++;
		}
		else {
			encodedChars.push_back(encodedString.substr(idx,1));
		}
	}


	std::string decodedStr;
	for(const std::string & encodedChar : encodedChars) {
		if(encodedChar.size() == 1) {
			decodedStr.push_back(encodedChar[0]);
		}
		else {
			if(encodedChar == "\\n") {
				decodedStr.push_back('\n');
			}
			if(encodedChar == "\\t") {
				decodedStr.push_back('\t');
			}
			if(encodedChar == "\\\"") {
				decodedStr.push_back('"');
			}
			if(encodedChar == "\\\\") {
				decodedStr.push_back('\\');
			}
		}
	}
	return decodedStr;
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

void ltn::Assembler::fFormat(InstCode code, HeapType type) {
	return this->fFormat(code, static_cast<std::uint8_t>(type));
}

void ltn::Assembler::fFormat(InstCode code, OuputFormat format) {
	return this->fFormat(code, static_cast<std::uint8_t>(format));
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

void ltn::Assembler::dFormat(InstCode code, std::uint64_t arg56) {
	std::uint64_t inst = 0;
	inst |= static_cast<std::uint64_t>(code);
	inst |= static_cast<std::uint64_t>(arg56) << 8;
	this->instructions.push_back(inst);
}