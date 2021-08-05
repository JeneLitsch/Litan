#include "LtnaAssembler.hxx"
#include <sstream>
#include <iostream>
#include <iomanip>
#include "LtnaStringDecoder.hxx"
#include "LtnaNumberParser.hxx"
#include "LtnaInstructionBuilder.hxx"

#include "LtnaUnknownInstruction.hxx"

// interate over code to find and save markers with their jump addresses
ltna::MarkerTable ltna::Assembler::searchMarkers(const std::vector<TokenPackage> & tokenPackages) {
	MarkerTable markerTable;
	std::size_t cmdNr = 0;
	for(const TokenPackage & pkg : tokenPackages){		
		if(pkg.inst == "") {}
		if(pkg.inst == "//") {}
		else if(pkg.inst == "->") {
			// + 1 because of goto MAIN
			markerTable.add(pkg.args[0], cmdNr + 1);
		}
		else{
			cmdNr++;
		}
	}
	return markerTable;
}

// assemble code
std::vector<std::uint64_t> ltna::Assembler::assemble(const std::vector<TokenPackage> & tokens) {
		
	std::vector<std::uint64_t> instructions;
	MarkerTable markerTable = this->searchMarkers(tokens);
	
	instructions.push_back(this->toInstruction(TokenPackage("<automatic>", "goto", {"MAIN"}, 0), markerTable));
	for(const TokenPackage & pkg : tokens) {
		if(pkg.inst == "") continue;
		if(pkg.inst == "//") continue;
		if(pkg.inst == "->") continue;
		instructions.push_back(this->toInstruction(pkg, markerTable));
	}
	return instructions;
}




std::uint64_t ltna::Assembler::toInstruction(
	const TokenPackage & pkg,
	const MarkerTable & markerTable) const {

	if(pkg.args.size() == 0) {
		if(pkg.inst == "exit") return cFormat(InstCode::EXIT);
		if(pkg.inst == "error") return cFormat(InstCode::ERROR);
		if(pkg.inst == "scrap") return cFormat(InstCode::SCRAP); 
		if(pkg.inst == "clear") return cFormat(InstCode::CLEAR); 
		if(pkg.inst == "copy") return cFormat(InstCode::COPY);
		if(pkg.inst == "size") return cFormat(InstCode::SIZE);
		if(pkg.inst == "init") return cFormat(InstCode::INIT);

		if(pkg.inst == "print::newline") return fFormat(InstCode::PRINT, ltn::OuputFormat::NEWLINE);
		if(pkg.inst == "print::int") return fFormat(InstCode::PRINT, ltn::OuputFormat::INT);
		if(pkg.inst == "print::uint") return fFormat(InstCode::PRINT, ltn::OuputFormat::UINT);
		if(pkg.inst == "print::bool") return fFormat(InstCode::PRINT, ltn::OuputFormat::BOOL);
		if(pkg.inst == "print::float") return fFormat(InstCode::PRINT, ltn::OuputFormat::FLOAT);
		if(pkg.inst == "print::string") return fFormat(InstCode::PRINT, ltn::OuputFormat::STRING);

		if(pkg.inst == "addi") return cFormat(InstCode::ADDI);
		if(pkg.inst == "subi") return cFormat(InstCode::SUBI);
		if(pkg.inst == "mlti") return cFormat(InstCode::MLTI);
		if(pkg.inst == "divi") return cFormat(InstCode::DIVI);
		if(pkg.inst == "powi") return cFormat(InstCode::POWI);
		if(pkg.inst == "modi") return cFormat(InstCode::MODI);

		if(pkg.inst == "inc") return cFormat(InstCode::INCI);
		if(pkg.inst == "dec") return cFormat(InstCode::DECI);
		if(pkg.inst == "inci") return cFormat(InstCode::INCI);
		if(pkg.inst == "deci") return cFormat(InstCode::DECI);

		if(pkg.inst == "incf") std::runtime_error("Flaoting point incrementation not valid");
		if(pkg.inst == "decf") std::runtime_error("Flaoting point decrementation not valid");

		if(pkg.inst == "mnsi") return cFormat(InstCode::MNSI);
		if(pkg.inst == "mnsf") return cFormat(InstCode::MNSF);
		if(pkg.inst == "mini") return cFormat(InstCode::MINI);
		if(pkg.inst == "minf") return cFormat(InstCode::MINF);
		if(pkg.inst == "maxi") return cFormat(InstCode::MAXI);
		if(pkg.inst == "maxf") return cFormat(InstCode::MAXF);

		if(pkg.inst == "addf") return cFormat(InstCode::ADDF);
		if(pkg.inst == "subf") return cFormat(InstCode::SUBF);
		if(pkg.inst == "mltf") return cFormat(InstCode::MLTF);
		if(pkg.inst == "divf") return cFormat(InstCode::DIVF);
		if(pkg.inst == "powf") return cFormat(InstCode::POWF);
		if(pkg.inst == "modf") return cFormat(InstCode::MODF);
		
		if(pkg.inst == "bitor") return cFormat(InstCode::BITOR);
		if(pkg.inst == "bitand") return cFormat(InstCode::BITAND);
		if(pkg.inst == "bitxor") return cFormat(InstCode::BITXOR);
		if(pkg.inst == "bitnot") return cFormat(InstCode::BITNOT);

		if(pkg.inst == "logor") return cFormat(InstCode::LOGOR);
		if(pkg.inst == "logand") return cFormat(InstCode::LOGAND);
		if(pkg.inst == "logxor") return cFormat(InstCode::LOGXOR);
		if(pkg.inst == "lognot") return cFormat(InstCode::LOGNOT);

		if(pkg.inst == "eqli") return cFormat(InstCode::EQLI);
		if(pkg.inst == "smli") return cFormat(InstCode::SMLI);
		if(pkg.inst == "bgri") return cFormat(InstCode::BGRI);

		if(pkg.inst == "eqlf") return cFormat(InstCode::EQLF);
		if(pkg.inst == "smlf") return cFormat(InstCode::SMLF);
		if(pkg.inst == "bgrf") return cFormat(InstCode::BGRF);

		if(pkg.inst == "casti") return fFormat(InstCode::CASTI, 0);
		if(pkg.inst == "castf") return fFormat(InstCode::CASTF, 0);

		if(pkg.inst == "return") return cFormat(InstCode::RETURN);
		if(pkg.inst == "ifnx") return cFormat(InstCode::IFSK);

		if(pkg.inst == "spshi") return cFormat(InstCode::SPSHI);
		if(pkg.inst == "spshf") return cFormat(InstCode::SPSHF);

		if(pkg.inst == "load") return cFormat(InstCode::LOAD); 
		if(pkg.inst == "store") return cFormat(InstCode::STORE); 
		
		if(pkg.inst == "heap::allocate::array") return fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::ARRAY);  
		if(pkg.inst == "heap::allocate::stack") return fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::STACK);  
		if(pkg.inst == "heap::allocate::queue") return fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::QUEUE);  
		if(pkg.inst == "heap::allocate::deque") return fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::DEQUE);  
		if(pkg.inst == "heap::allocate::string") return fFormat(InstCode::HEAP_ALLOCATE, ltn::HeapType::STRING);  
		if(pkg.inst == "heap::delete") return cFormat(InstCode::HEAP_DELETE);  
		if(pkg.inst == "heap::exist") return cFormat(InstCode::HEAP_EXIST);
		if(pkg.inst == "heap::istype::array") return fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::ARRAY);
		if(pkg.inst == "heap::istype::stack") return fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::STACK);
		if(pkg.inst == "heap::istype::queue") return fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::QUEUE);
		if(pkg.inst == "heap::istype::deque") return fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::DEQUE);
		if(pkg.inst == "heap::istype::string") return fFormat(InstCode::HEAP_ISTYPE, ltn::HeapType::STRING);
		if(pkg.inst == "heap::copy") return cFormat(InstCode::HEAP_COPY);

		if(pkg.inst == "array::set") return cFormat(InstCode::ARRAY_SET);  
		if(pkg.inst == "array::get") return cFormat(InstCode::ARRAY_GET);  
		if(pkg.inst == "array::clear") return cFormat(InstCode::ARRAY_CLEAR);  
		if(pkg.inst == "array::size") return cFormat(InstCode::ARRAY_SIZE);  
		if(pkg.inst == "array::empty") return cFormat(InstCode::ARRAY_EMPTY);  
		if(pkg.inst == "array::fill") return cFormat(InstCode::ARRAY_FILL);  
		if(pkg.inst == "array::resize") return cFormat(InstCode::ARRAY_RESIZE);  
		if(pkg.inst == "array::erase") return cFormat(InstCode::ARRAY_ERASE);  
		if(pkg.inst == "array::insert") return cFormat(InstCode::ARRAY_INSERT);  
		if(pkg.inst == "array::pushback") return cFormat(InstCode::ARRAY_PUSHB);  
		if(pkg.inst == "array::popback") return cFormat(InstCode::ARRAY_POPB);
		if(pkg.inst == "array::front") return cFormat(InstCode::ARRAY_FRONT);
		if(pkg.inst == "array::back") return cFormat(InstCode::ARRAY_BACK);

		if(pkg.inst == "stack::push") return cFormat(InstCode::STACK_PUSH);  
		if(pkg.inst == "stack::pop") return cFormat(InstCode::STACK_POP);  
		if(pkg.inst == "stack::top") return cFormat(InstCode::STACK_TOP);  
		if(pkg.inst == "stack::size") return cFormat(InstCode::STACK_SIZE);  
		if(pkg.inst == "stack::empty") return cFormat(InstCode::STACK_EMPTY);  
		if(pkg.inst == "stack::clear") return cFormat(InstCode::STACk_CLEAR);  

		if(pkg.inst == "queue::push") return cFormat(InstCode::QUEUE_PUSH);  
		if(pkg.inst == "queue::pop") return cFormat(InstCode::QUEUE_POP);  
		if(pkg.inst == "queue::front") return cFormat(InstCode::QUEUE_FRONT);  
		if(pkg.inst == "queue::size") return cFormat(InstCode::QUEUE_SIZE);  
		if(pkg.inst == "queue::empty") return cFormat(InstCode::QUEUE_EMPTY);  
		if(pkg.inst == "queue::clear") return cFormat(InstCode::QUEUE_CLEAR);  

		if(pkg.inst == "deque::pushf") return cFormat(InstCode::DEQUE_PUSHF);  
		if(pkg.inst == "deque::pushb") return cFormat(InstCode::DEQUE_PUSHB);  
		if(pkg.inst == "deque::popf") return cFormat(InstCode::DEQUE_POPF);  
		if(pkg.inst == "deque::popb") return cFormat(InstCode::DEQUE_POPB);  
		if(pkg.inst == "deque::front") return cFormat(InstCode::DEQUE_FRONT);  
		if(pkg.inst == "deque::back") return cFormat(InstCode::DEQUE_BACK);  
		if(pkg.inst == "deque::size") return cFormat(InstCode::DEQUE_SIZE);  
		if(pkg.inst == "deque::empty") return cFormat(InstCode::DEQUE_EMPTY);  
		if(pkg.inst == "deque::clear") return cFormat(InstCode::DEQUE_CLEAR);  

		if(pkg.inst == "string::add") return cFormat(InstCode::STRING_ADD);  

		if(pkg.inst == "loop::inf") return cFormat(InstCode::LOOP_INF);  
		if(pkg.inst == "loop::range") return cFormat(InstCode::LOOP_RANGE);
		if(pkg.inst == "loop::cont") return cFormat(InstCode::LOOP_CONT);  
		if(pkg.inst == "loop::stop") return cFormat(InstCode::LOOP_STOP);
		if(pkg.inst == "loop::idx") return cFormat(InstCode::LOOP_IDX);  
	}
	if(pkg.args.size() == 1) {
		if(pkg.inst == "casti") return fFormat(InstCode::CASTI, toInt8(pkg.args[0]));
		
		if(pkg.inst == "ext::0") return fFormat(InstCode::EXT0, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::1") return fFormat(InstCode::EXT1, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::2") return fFormat(InstCode::EXT2, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::3") return fFormat(InstCode::EXT3, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::4") return fFormat(InstCode::EXT4, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::5") return fFormat(InstCode::EXT5, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::6") return fFormat(InstCode::EXT6, toInt8(pkg.args[0]));  
		if(pkg.inst == "ext::7") return fFormat(InstCode::EXT7, toInt8(pkg.args[0]));  

		if(pkg.inst == "call") return jFormat(InstCode::CALL, markerTable.find(pkg.args[0]));  
		if(pkg.inst == "goto") return jFormat(InstCode::GOTO, markerTable.find(pkg.args[0]));  

		if(pkg.inst == "newl") return vFormat(InstCode::NEWL, toInt32(pkg.args[0])); 
		if(pkg.inst == "newu") return vFormat(InstCode::NEWU, toInt32(pkg.args[0])); 
		if(pkg.inst == "stackalloc") return vFormat(InstCode::STACKALLOC, toInt32(pkg.args[0])); 
	}
	if(pkg.inst == "string::data") return dFormat(pkg.args);
	throw UnknownInstruction(pkg.inst, pkg.lineNr);
}




