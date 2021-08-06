#include "LtnaAssembler.hxx"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <functional>
#include "LtnaStringDecoder.hxx"
#include "LtnaNumberParser.hxx"
#include "LtnaInstructionBuilder.hxx"

#include "LtnaUnknownInstruction.hxx"

namespace ltna {

	using InstCreateFx = std::function<std::uint64_t(
		const std::vector<std::string> &,
		const MarkerTable &)>;

	struct InstructionInfo {
		InstructionInfo(InstCreateFx makeInst) : makeInst(makeInst) {}
		InstCreateFx makeInst;
	};

	using TranslationBlock = std::unordered_map<std::string, InstructionInfo>;
	using TranslationTable = std::unordered_map<int, TranslationBlock>;

	template<class ... Args> 
	InstCreateFx fx(auto function, const Args & ... args) {
		return std::bind(function, args...);
	}

	static const TranslationTable translationTable = {
		{0, TranslationBlock{
			{ "exit", { fx(inst1, InstCode::EXIT)}},
			{ "error", { fx(inst1, InstCode::ERROR)}},
			{ "scrap", { fx(inst1, InstCode::SCRAP)}},
			{ "clear", { fx(inst1, InstCode::CLEAR)}},
			{ "copy", { fx(inst1, InstCode::COPY)}},
			{ "size", { fx(inst1, InstCode::SIZE)}},
			
			{ "print::newline", { fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::NEWLINE)}},
			{ "print::int", { fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::INT)}},
			{ "print::uint", { fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::UINT)}},
			{ "print::bool", { fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::BOOL)}},
			{ "print::float", { fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::FLOAT)}},
			{ "print::string", { fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::STRING)}},

			{ "addi", { fx(inst1, InstCode::ADDI)}}, 
			{ "subi", { fx(inst1, InstCode::SUBI)}}, 
			{ "mlti", { fx(inst1, InstCode::MLTI)}}, 
			{ "divi", { fx(inst1, InstCode::DIVI)}}, 
			{ "modi", { fx(inst1, InstCode::MODI)}}, 
			{ "powi", { fx(inst1, InstCode::POWI)}},
			{ "inc",  { fx(inst1, InstCode::INCI)}},
			{ "dec",  { fx(inst1, InstCode::DECI)}},
			{ "inci", { fx(inst1, InstCode::INCI)}},
			{ "deci", { fx(inst1, InstCode::DECI)}},
			{ "mnsi", { fx(inst1, InstCode::MNSI)}},
			{ "mini", { fx(inst1, InstCode::MINI)}},
			{ "maxi", { fx(inst1, InstCode::MAXI)}},

			{ "eqli", { fx(inst1, InstCode::EQLI)}},
			{ "smli", { fx(inst1, InstCode::SMLI)}},
			{ "bgri", { fx(inst1, InstCode::BGRI)}},
			{ "spshi", { fx(inst1, InstCode::SPSHI)}},
		
			{ "addf", { fx(inst1, InstCode::ADDF)}}, 
			{ "subf", { fx(inst1, InstCode::SUBF)}}, 
			{ "mltf", { fx(inst1, InstCode::MLTF)}}, 
			{ "divf", { fx(inst1, InstCode::DIVF)}}, 
			{ "modf", { fx(inst1, InstCode::MODF)}}, 
			{ "powf", { fx(inst1, InstCode::POWF)}},
			{ "mnsf", { fx(inst1, InstCode::MNSF)}},
			{ "minf", { fx(inst1, InstCode::MINF)}},
			{ "maxf", { fx(inst1, InstCode::MAXF)}},

			{ "eqlf", { fx(inst1, InstCode::EQLF)}},
			{ "smlf", { fx(inst1, InstCode::SMLF)}},
			{ "bgrf", { fx(inst1, InstCode::BGRF)}},
			{ "spshf", { fx(inst1, InstCode::SPSHF)}},

			{ "bitor", { fx(inst1, InstCode::BITOR)}},
			{ "bitand", { fx(inst1, InstCode::BITAND)}},
			{ "bitxor", { fx(inst1, InstCode::BITXOR)}},
			{ "bitnot", { fx(inst1, InstCode::BITNOT)}},
		
			{ "logor", { fx(inst1, InstCode::LOGOR)}},
			{ "logand", { fx(inst1, InstCode::LOGAND)}},
			{ "logxor", { fx(inst1, InstCode::LOGXOR)}},
			{ "lognot", { fx(inst1, InstCode::LOGNOT)}},

			{ "casti", { fx(inst2Funct, InstCode::CASTI, 0)}},
			{ "castf", { fx(inst2Funct, InstCode::CASTF, 0)}},

			{ "return", { fx(inst1, InstCode::RETURN)}},
			{ "ifnx", { fx(inst1, InstCode::IFSK)}},

			{ "load", { fx(inst1, InstCode::LOAD)}},
			{ "store", { fx(inst1, InstCode::STORE)}},

			{ "heap::delete", { fx(inst1, InstCode::HEAP_DELETE)}},
			{ "heap::exist", { fx(inst1, InstCode::HEAP_EXIST)}},
			{ "heap::copy", { fx(inst1, InstCode::HEAP_COPY)}},
			{ "heap::allocate::array", { fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::ARRAY)}},
			{ "heap::allocate::stack", { fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::STACK)}},
			{ "heap::allocate::queue", { fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::QUEUE)}},
			{ "heap::allocate::deque", { fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::DEQUE)}},
			{ "heap::allocate::string", { fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::STRING)}},
			{ "heap::istype::array", { fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::ARRAY)}},
			{ "heap::istype::stack", { fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::STACK)}},
			{ "heap::istype::queue", { fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::QUEUE)}},
			{ "heap::istype::deque", { fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::DEQUE)}},
			{ "heap::istype::string", { fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::STRING)}},

			{ "array::set", { fx(inst1, InstCode::ARRAY_SET)}},
			{ "array::get", { fx(inst1, InstCode::ARRAY_GET)}},
			{ "array::clear", { fx(inst1, InstCode::ARRAY_CLEAR)}},
			{ "array::size", { fx(inst1, InstCode::ARRAY_SIZE)}},
			{ "array::empty", { fx(inst1, InstCode::ARRAY_EMPTY)}},
			{ "array::fill", { fx(inst1, InstCode::ARRAY_FILL)}},
			{ "array::resize", { fx(inst1, InstCode::ARRAY_RESIZE)}},
			{ "array::erase", { fx(inst1, InstCode::ARRAY_ERASE)}},
			{ "array::insert", { fx(inst1, InstCode::ARRAY_INSERT)}},
			{ "array::pushback", { fx(inst1, InstCode::ARRAY_PUSHB)}},
			{ "array::popback", { fx(inst1, InstCode::ARRAY_POPB)}},
			{ "array::front", { fx(inst1, InstCode::ARRAY_FRONT)}},
			{ "array::back", { fx(inst1, InstCode::ARRAY_BACK)}},

			{ "stack::push", { fx(inst1, InstCode::STACK_PUSH)}},
			{ "stack::pop", { fx(inst1, InstCode::STACK_POP)}},
			{ "stack::top", { fx(inst1, InstCode::STACK_TOP)}},
			{ "stack::size", { fx(inst1, InstCode::STACK_SIZE)}},
			{ "stack::empty", { fx(inst1, InstCode::STACK_EMPTY)}},
			{ "stack::clear", { fx(inst1, InstCode::STACk_CLEAR)}},

			{ "queue::push", { fx(inst1, InstCode::QUEUE_PUSH)}},
			{ "queue::pop", { fx(inst1, InstCode::QUEUE_POP)}},
			{ "queue::front", { fx(inst1, InstCode::QUEUE_FRONT)}},
			{ "queue::size", { fx(inst1, InstCode::QUEUE_SIZE)}},
			{ "queue::empty", { fx(inst1, InstCode::QUEUE_EMPTY)}},
			{ "queue::clear", { fx(inst1, InstCode::QUEUE_CLEAR)}},

			{ "deque::pushf", { fx(inst1, InstCode::DEQUE_PUSHF)}},
			{ "deque::pushb", { fx(inst1, InstCode::DEQUE_PUSHB)}},
			{ "deque::popf", { fx(inst1, InstCode::DEQUE_POPF)}},
			{ "deque::popb", { fx(inst1, InstCode::DEQUE_POPB)}},
			{ "deque::front", { fx(inst1, InstCode::DEQUE_FRONT)}},
			{ "deque::back", { fx(inst1, InstCode::DEQUE_BACK)}},
			{ "deque::size", { fx(inst1, InstCode::DEQUE_SIZE)}},
			{ "deque::empty", { fx(inst1, InstCode::DEQUE_EMPTY)}},
			{ "deque::clear", { fx(inst1, InstCode::DEQUE_CLEAR)}},

			{ "string::add", { fx(inst1, InstCode::STRING_ADD)}},

			{ "loop::inf", { fx(inst1, InstCode::LOOP_INF)}},
			{ "loop::range", { fx(inst1, InstCode::LOOP_RANGE)}},
			{ "loop::cont", { fx(inst1, InstCode::LOOP_CONT)}},
			{ "loop::stop", { fx(inst1, InstCode::LOOP_STOP)}},
			{ "loop::idx", { fx(inst1, InstCode::LOOP_IDX)}},

		}},
		{1, TranslationBlock{
			{ "casti", {[](auto args, auto) { return inst2Funct(InstCode::CASTI, toInt8(args[0])); }}},
			
			{ "ext::0", {[](auto args, auto) { return inst2Funct(InstCode::EXT0, toInt8(args[0])); }}},
			{ "ext::1", {[](auto args, auto) { return inst2Funct(InstCode::EXT1, toInt8(args[0])); }}},
			{ "ext::2", {[](auto args, auto) { return inst2Funct(InstCode::EXT2, toInt8(args[0])); }}},
			{ "ext::3", {[](auto args, auto) { return inst2Funct(InstCode::EXT3, toInt8(args[0])); }}},
			{ "ext::4", {[](auto args, auto) { return inst2Funct(InstCode::EXT4, toInt8(args[0])); }}},
			{ "ext::5", {[](auto args, auto) { return inst2Funct(InstCode::EXT5, toInt8(args[0])); }}},
			{ "ext::6", {[](auto args, auto) { return inst2Funct(InstCode::EXT6, toInt8(args[0])); }}},
			{ "ext::7", {[](auto args, auto) { return inst2Funct(InstCode::EXT7, toInt8(args[0])); }}},

			{ "call", {[](auto args, auto markerTable) { return inst8(InstCode::CALL, markerTable.find(args[0])); }}},
			{ "goto", {[](auto args, auto markerTable) { return inst8(InstCode::GOTO, markerTable.find(args[0])); }}},

			{ "newl", {[](auto args, auto) { return inst4(InstCode::NEWL, toInt32(args[0])); }}},
			{ "newu", {[](auto args, auto) { return inst4(InstCode::NEWU, toInt32(args[0])); }}},
			{ "stackalloc", {[](auto args, auto) { return inst4(InstCode::STACKALLOC, toInt32(args[0])); }}},
		}},
		{-1, TranslationBlock{
			{ "string::data", InstructionInfo([](auto args, auto) { return instX(InstCode::STRING_DATA, args); })},
		}},
	};
}

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

	if(translationTable.contains(pkg.args.size())) {
		const TranslationBlock & block = translationTable.at(pkg.args.size());
		if(block.contains(pkg.inst)) {
			const InstructionInfo & instInfo = block.at(pkg.inst);
			return instInfo.makeInst(pkg.args, markerTable);
		}
	}
	else if(translationTable.contains(-1)) {
		const TranslationBlock & block = translationTable.at(-1);
		if(block.contains(pkg.inst)) {
			const InstructionInfo & instInfo = block.at(pkg.inst);
			return instInfo.makeInst(pkg.args, markerTable);
		}
	}
	throw UnknownInstruction(pkg.inst, pkg.lineNr);
}




