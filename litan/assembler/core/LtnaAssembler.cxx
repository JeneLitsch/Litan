#include "LtnaAssembler.hxx"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <functional>
#include "LtnaStringDecoder.hxx"
#include "LtnaNumberParser.hxx"
#include "LtnaInstructionBuilder.hxx"

#include "LtnaUnknownInstruction.hxx"
using namespace std;

namespace ltn::a {

	using InstCreateFx = std::function<std::uint64_t(
		const std::vector<std::string> &,
		const MarkerTable &)>;

	struct InstructionInfo {
		InstructionInfo(
			InstCreateFx makeInst)
			: makeInst(makeInst) {}
		InstCreateFx makeInst;
	};

	using TranslationBlock = std::unordered_map<std::string, InstructionInfo>;
	using TranslationTable = std::unordered_map<int, TranslationBlock>;

	template<class ... Args> 
	InstCreateFx fx(auto function, const Args & ... args) {
		return std::bind(function, args...);
	}

	static const TranslationTable translationTable = {
		// No arguments
		{0, {
			{ "exit", { fx(cInst, InstCode::EXIT)}},
			{ "error", { fx(cInst, InstCode::ERROR)}},
			{ "scrap", { fx(cInst, InstCode::SCRAP)}},
			{ "copy", { fx(cInst, InstCode::COPY)}},
			
			{ "print::newline", { fx(fInstFormat, InstCode::PRINT, ltn::OuputFormat::NEWLINE)}},
			{ "print::int", { fx(fInstFormat, InstCode::PRINT, ltn::OuputFormat::INT)}},
			{ "print::uint", { fx(fInstFormat, InstCode::PRINT, ltn::OuputFormat::UINT)}},
			{ "print::bool", { fx(fInstFormat, InstCode::PRINT, ltn::OuputFormat::BOOL)}},
			{ "print::float", { fx(fInstFormat, InstCode::PRINT, ltn::OuputFormat::FLOAT)}},
			{ "print::string", { fx(fInstFormat, InstCode::PRINT, ltn::OuputFormat::STRING)}},

			{ "addi", { fx(cInst, InstCode::ADDI)}}, 
			{ "subi", { fx(cInst, InstCode::SUBI)}}, 
			{ "mlti", { fx(cInst, InstCode::MLTI)}}, 
			{ "divi", { fx(cInst, InstCode::DIVI)}}, 
			{ "modi", { fx(cInst, InstCode::MODI)}}, 
			{ "powi", { fx(cInst, InstCode::POWI)}},
			{ "inc",  { fx(cInst, InstCode::INCI)}},
			{ "dec",  { fx(cInst, InstCode::DECI)}},
			{ "inci", { fx(cInst, InstCode::INCI)}},
			{ "deci", { fx(cInst, InstCode::DECI)}},
			{ "mnsi", { fx(cInst, InstCode::MNSI)}},
			{ "mini", { fx(cInst, InstCode::MINI)}},
			{ "maxi", { fx(cInst, InstCode::MAXI)}},

			{ "eqli", { fx(cInst, InstCode::EQLI)}},
			{ "uneqli", { fx(fInstFunct, InstCode::EQLI, 1)}},
			{ "smli", { fx(cInst, InstCode::SMLI)}},
			{ "bgri", { fx(cInst, InstCode::BGRI)}},
			{ "spshi", { fx(cInst, InstCode::SPSHI)}},
		
			{ "addf", { fx(cInst, InstCode::ADDF)}}, 
			{ "subf", { fx(cInst, InstCode::SUBF)}}, 
			{ "mltf", { fx(cInst, InstCode::MLTF)}}, 
			{ "divf", { fx(cInst, InstCode::DIVF)}}, 
			{ "modf", { fx(cInst, InstCode::MODF)}}, 
			{ "powf", { fx(cInst, InstCode::POWF)}},
			{ "mnsf", { fx(cInst, InstCode::MNSF)}},
			{ "minf", { fx(cInst, InstCode::MINF)}},
			{ "maxf", { fx(cInst, InstCode::MAXF)}},

			{ "eqlf", { fx(cInst, InstCode::EQLF)}},
			{ "uneqlf", { fx(fInstFunct, InstCode::EQLF, 1)}},
			{ "smlf", { fx(cInst, InstCode::SMLF)}},
			{ "bgrf", { fx(cInst, InstCode::BGRF)}},
			{ "spshf", { fx(cInst, InstCode::SPSHF)}},

			{ "bitor", { fx(cInst, InstCode::BITOR)}},
			{ "bitand", { fx(cInst, InstCode::BITAND)}},
			{ "bitxor", { fx(cInst, InstCode::BITXOR)}},
			{ "bitnot", { fx(cInst, InstCode::BITNOT)}},
		
			{ "logor", { fx(cInst, InstCode::LOGOR)}},
			{ "logand", { fx(cInst, InstCode::LOGAND)}},
			{ "logxor", { fx(cInst, InstCode::LOGXOR)}},
			{ "lognot", { fx(cInst, InstCode::LOGNOT)}},

			{ "casti", { fx(fInstFunct, InstCode::CASTI, 0)}},
			{ "castf", { fx(fInstFunct, InstCode::CASTF, 0)}},

			{ "return", { fx(cInst, InstCode::RETURN)}},
			{ "ifnx", { fx(cInst, InstCode::IFNX)}},

			{ "load", { fx(cInst, InstCode::LOAD)}},
			{ "store", { fx(cInst, InstCode::STORE)}},

			{ "sort::radix::desc::unsigned",	{ fx(fInstFunct, InstCode::SORT_RADIX, 0b10)}},
			{ "sort::radix::desc::signed", 		{ fx(fInstFunct, InstCode::SORT_RADIX, 0b11)}},
			{ "sort::radix::ascn::unsigned",	{ fx(fInstFunct, InstCode::SORT_RADIX, 0b00)}},
			{ "sort::radix::ascn::signed", 		{ fx(fInstFunct, InstCode::SORT_RADIX, 0b01)}},

			{ "rand::int",		{ fx(cInst, InstCode::RAND_INT)}},
			{ "rand::float",	{ fx(cInst, InstCode::RAND_FLOAT)}},
			{ "rand::norm",		{ fx(cInst, InstCode::RAND_NORM)}},
			{ "rand::unit",		{ fx(cInst, InstCode::RAND_UNIT)}},


			{ "heap::delete", { fx(cInst, InstCode::HEAP_DELETE)}},
			{ "heap::exist", { fx(cInst, InstCode::HEAP_EXIST)}},
			{ "heap::copy", { fx(cInst, InstCode::HEAP_COPY)}},
			{ "heap::allocate::array", { fx(fInstType, InstCode::HEAP_ALLOCATE, ltn::HeapType::ARRAY)}},
			{ "heap::allocate::stack", { fx(fInstType, InstCode::HEAP_ALLOCATE, ltn::HeapType::STACK)}},
			{ "heap::allocate::queue", { fx(fInstType, InstCode::HEAP_ALLOCATE, ltn::HeapType::QUEUE)}},
			{ "heap::allocate::deque", { fx(fInstType, InstCode::HEAP_ALLOCATE, ltn::HeapType::DEQUE)}},
			{ "heap::allocate::string", { fx(fInstType, InstCode::HEAP_ALLOCATE, ltn::HeapType::STRING)}},
			{ "heap::istype::array", { fx(fInstType, InstCode::HEAP_ISTYPE, ltn::HeapType::ARRAY)}},
			{ "heap::istype::stack", { fx(fInstType, InstCode::HEAP_ISTYPE, ltn::HeapType::STACK)}},
			{ "heap::istype::queue", { fx(fInstType, InstCode::HEAP_ISTYPE, ltn::HeapType::QUEUE)}},
			{ "heap::istype::deque", { fx(fInstType, InstCode::HEAP_ISTYPE, ltn::HeapType::DEQUE)}},
			{ "heap::istype::string", { fx(fInstType, InstCode::HEAP_ISTYPE, ltn::HeapType::STRING)}},

			{ "array::set", { fx(cInst, InstCode::ARRAY_SET)}},
			{ "array::get", { fx(cInst, InstCode::ARRAY_GET)}},
			{ "array::clear", { fx(cInst, InstCode::ARRAY_CLEAR)}},
			{ "array::size", { fx(cInst, InstCode::ARRAY_SIZE)}},
			{ "array::empty", { fx(cInst, InstCode::ARRAY_EMPTY)}},
			{ "array::fill", { fx(cInst, InstCode::ARRAY_FILL)}},
			{ "array::resize", { fx(cInst, InstCode::ARRAY_RESIZE)}},
			{ "array::erase", { fx(cInst, InstCode::ARRAY_ERASE)}},
			{ "array::insert", { fx(cInst, InstCode::ARRAY_INSERT)}},
			{ "array::pushback", { fx(cInst, InstCode::ARRAY_PUSHB)}},
			{ "array::popback", { fx(cInst, InstCode::ARRAY_POPB)}},
			{ "array::front", { fx(cInst, InstCode::ARRAY_FRONT)}},
			{ "array::back", { fx(cInst, InstCode::ARRAY_BACK)}},

			{ "stack::push", { fx(cInst, InstCode::STACK_PUSH)}},
			{ "stack::pop", { fx(cInst, InstCode::STACK_POP)}},
			{ "stack::top", { fx(cInst, InstCode::STACK_TOP)}},
			{ "stack::size", { fx(cInst, InstCode::STACK_SIZE)}},
			{ "stack::empty", { fx(cInst, InstCode::STACK_EMPTY)}},
			{ "stack::clear", { fx(cInst, InstCode::STACk_CLEAR)}},

			{ "queue::push", { fx(cInst, InstCode::QUEUE_PUSH)}},
			{ "queue::pop", { fx(cInst, InstCode::QUEUE_POP)}},
			{ "queue::front", { fx(cInst, InstCode::QUEUE_FRONT)}},
			{ "queue::size", { fx(cInst, InstCode::QUEUE_SIZE)}},
			{ "queue::empty", { fx(cInst, InstCode::QUEUE_EMPTY)}},
			{ "queue::clear", { fx(cInst, InstCode::QUEUE_CLEAR)}},

			{ "deque::pushf", { fx(cInst, InstCode::DEQUE_PUSHF)}},
			{ "deque::pushb", { fx(cInst, InstCode::DEQUE_PUSHB)}},
			{ "deque::popf", { fx(cInst, InstCode::DEQUE_POPF)}},
			{ "deque::popb", { fx(cInst, InstCode::DEQUE_POPB)}},
			{ "deque::front", { fx(cInst, InstCode::DEQUE_FRONT)}},
			{ "deque::back", { fx(cInst, InstCode::DEQUE_BACK)}},
			{ "deque::size", { fx(cInst, InstCode::DEQUE_SIZE)}},
			{ "deque::empty", { fx(cInst, InstCode::DEQUE_EMPTY)}},
			{ "deque::clear", { fx(cInst, InstCode::DEQUE_CLEAR)}},

			{ "string::add", { fx(cInst, InstCode::STRING_ADD)}},

			{ "loop::inf", { fx(cInst, InstCode::LOOP_INF)}},
			{ "loop::range", { fx(cInst, InstCode::LOOP_RANGE)}},
			{ "loop::cont", { fx(cInst, InstCode::LOOP_CONT)}},
			{ "loop::stop", { fx(cInst, InstCode::LOOP_STOP)}},
			{ "loop::idx", { fx(cInst, InstCode::LOOP_IDX)}},

		}},
		// One argument
		{1, {
			{ "casti", {[](auto args, auto) { return fInstFunct(InstCode::CASTI, toInt8(args[0])); }}},
			
			{ "ext::0", {[](auto args, auto) { return fInstFunct(InstCode::EXT0, toInt8(args[0])); }}},
			{ "ext::1", {[](auto args, auto) { return fInstFunct(InstCode::EXT1, toInt8(args[0])); }}},
			{ "ext::2", {[](auto args, auto) { return fInstFunct(InstCode::EXT2, toInt8(args[0])); }}},
			{ "ext::3", {[](auto args, auto) { return fInstFunct(InstCode::EXT3, toInt8(args[0])); }}},
			{ "ext::4", {[](auto args, auto) { return fInstFunct(InstCode::EXT4, toInt8(args[0])); }}},
			{ "ext::5", {[](auto args, auto) { return fInstFunct(InstCode::EXT5, toInt8(args[0])); }}},
			{ "ext::6", {[](auto args, auto) { return fInstFunct(InstCode::EXT6, toInt8(args[0])); }}},
			{ "ext::7", {[](auto args, auto) { return fInstFunct(InstCode::EXT7, toInt8(args[0])); }}},

			{ "call", {[](auto args, auto markerTable) { return jInst(InstCode::CALL, markerTable.find(args[0])); }}},
			{ "goto", {[](auto args, auto markerTable) { return jInst(InstCode::GOTO, markerTable.find(args[0])); }}},

			{ "load", {[](auto args, auto) { return pInst(InstCode::LOAD, 1, toInt32(args[0])); }}},
			{ "store", {[](auto args, auto) { return pInst(InstCode::STORE, 1, toInt32(args[0])); }}},
			
			{ "newl", {[](auto args, auto) { return vInst(InstCode::NEWL, toInt32(args[0])); }}},
			{ "newu", {[](auto args, auto) { return vInst(InstCode::NEWU, toInt32(args[0])); }}},
			{ "stackalloc", {[](auto args, auto) { return vInst(InstCode::STACKALLOC, toInt32(args[0])); }}},
		}},
		// Multiple Argments
		{-1, {
			{ "string::data", InstructionInfo([](auto args, auto) { return xInst(InstCode::STRING_DATA, args); })},
		}},
	};

	// Iterate over instructions and track all jumpmarks
	MarkerTable searchMarkers(const std::vector<TokenPackage> & tokenPackages) {
		ltn::a::MarkerTable markerTable;
		std::size_t cmdNr = 0;
		for(const TokenPackage & pkg : tokenPackages){
			// ingore empty line	
			if(pkg.inst == "") {}
			// ingore comments
			if(pkg.inst == "//") {}
			// next instruction after jumpmark
			else if(pkg.inst == "->") {
				markerTable.add(pkg.args[0], cmdNr + 1);
			}
			else{
				cmdNr++;
			}
		}
		return markerTable;
	}

	// Find and returns a single Instruction
	const InstructionInfo & findInstruction(int blockId, const std::string & name) {
		if(translationTable.contains(blockId)) {
			const auto & block = translationTable.at(blockId);
			if(block.contains(name)) {
				return block.at(name);
			}
		}
		const auto & block = translationTable.at(-1);
		if(block.contains(name)) {
			return block.at(name);
		}
		throw UnknownInstruction(name, 0);
	}

	// Assembles a instruction to a 64-Bit/8-Byte Block 
	std::uint64_t toInstruction(
		const TokenPackage & pkg,
		const MarkerTable & markerTable) {
		int blockId = static_cast<int>(pkg.args.size());
		const auto instInfo = findInstruction(blockId, pkg.inst);
		return instInfo.makeInst(pkg.args, markerTable);
	}
}

// Assembles code to Instruction list
std::vector<std::uint64_t> ltn::a::Assembler::assemble(const std::vector<TokenPackage> & tokens) {

	std::vector<std::uint64_t> instructions;
	MarkerTable markerTable = searchMarkers(tokens);
	
	instructions.push_back(toInstruction(TokenPackage("<automatic>", "goto", {"MAIN"}, 0), markerTable));
	for(const TokenPackage & pkg : tokens) {
		if(pkg.inst == "") continue;
		if(pkg.inst == "//") continue;
		if(pkg.inst == "->") continue;
		instructions.push_back(toInstruction(pkg, markerTable));
	}
	return instructions;
}








