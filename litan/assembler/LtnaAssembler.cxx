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
		InstructionInfo(
			std::uint64_t length,
			InstCreateFx makeInst)
			: length(length), makeInst(makeInst) {}
		
		std::uint64_t length;
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
			{ "exit", { 1, fx(inst1, InstCode::EXIT)}},
			{ "error", { 1, fx(inst1, InstCode::ERROR)}},
			{ "scrap", { 1, fx(inst1, InstCode::SCRAP)}},
			{ "clear", { 1, fx(inst1, InstCode::CLEAR)}},
			{ "copy", { 1, fx(inst1, InstCode::COPY)}},
			{ "size", { 1, fx(inst1, InstCode::SIZE)}},
			
			{ "print::newline", { 2, fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::NEWLINE)}},
			{ "print::int", { 2, fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::INT)}},
			{ "print::uint", { 2, fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::UINT)}},
			{ "print::bool", { 2, fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::BOOL)}},
			{ "print::float", { 2, fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::FLOAT)}},
			{ "print::string", { 2, fx(inst2Format, InstCode::PRINT, ltn::OuputFormat::STRING)}},

			{ "addi", { 1, fx(inst1, InstCode::ADDI)}}, 
			{ "subi", { 1, fx(inst1, InstCode::SUBI)}}, 
			{ "mlti", { 1, fx(inst1, InstCode::MLTI)}}, 
			{ "divi", { 1, fx(inst1, InstCode::DIVI)}}, 
			{ "modi", { 1, fx(inst1, InstCode::MODI)}}, 
			{ "powi", { 1, fx(inst1, InstCode::POWI)}},
			{ "inc",  { 1, fx(inst1, InstCode::INCI)}},
			{ "dec",  { 1, fx(inst1, InstCode::DECI)}},
			{ "inci", { 1, fx(inst1, InstCode::INCI)}},
			{ "deci", { 1, fx(inst1, InstCode::DECI)}},
			{ "mnsi", { 1, fx(inst1, InstCode::MNSI)}},
			{ "mini", { 1, fx(inst1, InstCode::MINI)}},
			{ "maxi", { 1, fx(inst1, InstCode::MAXI)}},

			{ "eqli", { 1, fx(inst1, InstCode::EQLI)}},
			{ "smli", { 1, fx(inst1, InstCode::SMLI)}},
			{ "bgri", { 1, fx(inst1, InstCode::BGRI)}},
			{ "spshi", { 1, fx(inst1, InstCode::SPSHI)}},
		
			{ "addf", { 1, fx(inst1, InstCode::ADDF)}}, 
			{ "subf", { 1, fx(inst1, InstCode::SUBF)}}, 
			{ "mltf", { 1, fx(inst1, InstCode::MLTF)}}, 
			{ "divf", { 1, fx(inst1, InstCode::DIVF)}}, 
			{ "modf", { 1, fx(inst1, InstCode::MODF)}}, 
			{ "powf", { 1, fx(inst1, InstCode::POWF)}},
			{ "mnsf", { 1, fx(inst1, InstCode::MNSF)}},
			{ "minf", { 1, fx(inst1, InstCode::MINF)}},
			{ "maxf", { 1, fx(inst1, InstCode::MAXF)}},

			{ "eqlf", { 1,  fx(inst1, InstCode::EQLF)}},
			{ "smlf", { 1, fx(inst1, InstCode::SMLF)}},
			{ "bgrf", { 1, fx(inst1, InstCode::BGRF)}},
			{ "spshf", { 1, fx(inst1, InstCode::SPSHF)}},

			{ "bitor", { 1, fx(inst1, InstCode::BITOR)}},
			{ "bitand", { 1, fx(inst1, InstCode::BITAND)}},
			{ "bitxor", { 1, fx(inst1, InstCode::BITXOR)}},
			{ "bitnot", { 1, fx(inst1, InstCode::BITNOT)}},
		
			{ "logor", { 1, fx(inst1, InstCode::LOGOR)}},
			{ "logand", { 1, fx(inst1, InstCode::LOGAND)}},
			{ "logxor", { 1, fx(inst1, InstCode::LOGXOR)}},
			{ "lognot", { 1, fx(inst1, InstCode::LOGNOT)}},

			{ "casti", { 2, fx(inst2Funct, InstCode::CASTI, 0)}},
			{ "castf", { 2, fx(inst2Funct, InstCode::CASTF, 0)}},

			{ "return", { 1, fx(inst1, InstCode::RETURN)}},
			{ "ifnx", { 1, fx(inst1, InstCode::IFSK)}},

			{ "load", { 1, fx(inst1, InstCode::LOAD)}},
			{ "store", { 1, fx(inst1, InstCode::STORE)}},

			{ "heap::delete", { 1, fx(inst1, InstCode::HEAP_DELETE)}},
			{ "heap::exist", { 1, fx(inst1, InstCode::HEAP_EXIST)}},
			{ "heap::copy", { 1, fx(inst1, InstCode::HEAP_COPY)}},
			{ "heap::allocate::array", { 2, fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::ARRAY)}},
			{ "heap::allocate::stack", { 2, fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::STACK)}},
			{ "heap::allocate::queue", { 2, fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::QUEUE)}},
			{ "heap::allocate::deque", { 2, fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::DEQUE)}},
			{ "heap::allocate::string", { 2, fx(inst2Type, InstCode::HEAP_ALLOCATE, ltn::HeapType::STRING)}},
			{ "heap::istype::array", { 2, fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::ARRAY)}},
			{ "heap::istype::stack", { 2, fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::STACK)}},
			{ "heap::istype::queue", { 2, fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::QUEUE)}},
			{ "heap::istype::deque", { 2, fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::DEQUE)}},
			{ "heap::istype::string", { 2, fx(inst2Type, InstCode::HEAP_ISTYPE, ltn::HeapType::STRING)}},

			{ "array::set", { 1, fx(inst1, InstCode::ARRAY_SET)}},
			{ "array::get", { 1, fx(inst1, InstCode::ARRAY_GET)}},
			{ "array::clear", { 1, fx(inst1, InstCode::ARRAY_CLEAR)}},
			{ "array::size", { 1, fx(inst1, InstCode::ARRAY_SIZE)}},
			{ "array::empty", { 1, fx(inst1, InstCode::ARRAY_EMPTY)}},
			{ "array::fill", { 1, fx(inst1, InstCode::ARRAY_FILL)}},
			{ "array::resize", { 1, fx(inst1, InstCode::ARRAY_RESIZE)}},
			{ "array::erase", { 1, fx(inst1, InstCode::ARRAY_ERASE)}},
			{ "array::insert", { 1, fx(inst1, InstCode::ARRAY_INSERT)}},
			{ "array::pushback", { 1, fx(inst1, InstCode::ARRAY_PUSHB)}},
			{ "array::popback", { 1, fx(inst1, InstCode::ARRAY_POPB)}},
			{ "array::front", { 1, fx(inst1, InstCode::ARRAY_FRONT)}},
			{ "array::back", { 1, fx(inst1, InstCode::ARRAY_BACK)}},

			{ "stack::push", { 1, fx(inst1, InstCode::STACK_PUSH)}},
			{ "stack::pop", { 1, fx(inst1, InstCode::STACK_POP)}},
			{ "stack::top", { 1, fx(inst1, InstCode::STACK_TOP)}},
			{ "stack::size", { 1, fx(inst1, InstCode::STACK_SIZE)}},
			{ "stack::empty", { 1, fx(inst1, InstCode::STACK_EMPTY)}},
			{ "stack::clear", { 1, fx(inst1, InstCode::STACk_CLEAR)}},

			{ "queue::push", { 1, fx(inst1, InstCode::QUEUE_PUSH)}},
			{ "queue::pop", { 1, fx(inst1, InstCode::QUEUE_POP)}},
			{ "queue::front", { 1, fx(inst1, InstCode::QUEUE_FRONT)}},
			{ "queue::size", { 1, fx(inst1, InstCode::QUEUE_SIZE)}},
			{ "queue::empty", { 1, fx(inst1, InstCode::QUEUE_EMPTY)}},
			{ "queue::clear", { 1, fx(inst1, InstCode::QUEUE_CLEAR)}},

			{ "deque::pushf", { 1, fx(inst1, InstCode::DEQUE_PUSHF)}},
			{ "deque::pushb", { 1, fx(inst1, InstCode::DEQUE_PUSHB)}},
			{ "deque::popf", { 1, fx(inst1, InstCode::DEQUE_POPF)}},
			{ "deque::popb", { 1, fx(inst1, InstCode::DEQUE_POPB)}},
			{ "deque::front", { 1, fx(inst1, InstCode::DEQUE_FRONT)}},
			{ "deque::back", { 1, fx(inst1, InstCode::DEQUE_BACK)}},
			{ "deque::size", { 1, fx(inst1, InstCode::DEQUE_SIZE)}},
			{ "deque::empty", { 1, fx(inst1, InstCode::DEQUE_EMPTY)}},
			{ "deque::clear", { 1, fx(inst1, InstCode::DEQUE_CLEAR)}},

			{ "string::add", { 1, fx(inst1, InstCode::STRING_ADD)}},

			{ "loop::inf", { 1, fx(inst1, InstCode::LOOP_INF)}},
			{ "loop::range", { 1, fx(inst1, InstCode::LOOP_RANGE)}},
			{ "loop::cont", { 1, fx(inst1, InstCode::LOOP_CONT)}},
			{ "loop::stop", { 1, fx(inst1, InstCode::LOOP_STOP)}},
			{ "loop::idx", { 1, fx(inst1, InstCode::LOOP_IDX)}},

		}},
		{1, TranslationBlock{
			{ "casti", { 2, [](auto args, auto) { return inst2Funct(InstCode::CASTI, toInt8(args[0])); }}},
			
			{ "ext::0", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT0, toInt8(args[0])); }}},
			{ "ext::1", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT1, toInt8(args[0])); }}},
			{ "ext::2", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT2, toInt8(args[0])); }}},
			{ "ext::3", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT3, toInt8(args[0])); }}},
			{ "ext::4", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT4, toInt8(args[0])); }}},
			{ "ext::5", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT5, toInt8(args[0])); }}},
			{ "ext::6", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT6, toInt8(args[0])); }}},
			{ "ext::7", { 2, [](auto args, auto) { return inst2Funct(InstCode::EXT7, toInt8(args[0])); }}},

			{ "call", { 9, [](auto args, auto markerTable) { return inst9(InstCode::CALL, markerTable.find(args[0])); }}},
			{ "goto", { 9, [](auto args, auto markerTable) { return inst9(InstCode::GOTO, markerTable.find(args[0])); }}},

			{ "newl", { 5, [](auto args, auto) { return inst4(InstCode::NEWL, toInt32(args[0])); }}},
			{ "newu", { 5, [](auto args, auto) { return inst4(InstCode::NEWU, toInt32(args[0])); }}},
			{ "stackalloc", { 5,[](auto args, auto) { return inst4(InstCode::STACKALLOC, toInt32(args[0])); }}},
		}},
		{-1, TranslationBlock{
			{ "string::data", { 8, [](auto args, auto) { return instX(InstCode::STRING_DATA, args); }}},
		}},
	};

	// interate over code to find and save markers with their jump addresses
	MarkerTable searchMarkers(const std::vector<TokenPackage> & tokenPackages) {
		ltna::MarkerTable markerTable;
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

	std::uint64_t toInstruction(
		const TokenPackage & pkg,
		const MarkerTable & markerTable) {
		int blockId = static_cast<int>(pkg.args.size());
		const auto instInfo = findInstruction(blockId, pkg.inst);
		return instInfo.makeInst(pkg.args, markerTable);
	}
}

// assemble code
std::vector<std::uint64_t> ltna::Assembler::assemble(const std::vector<TokenPackage> & tokens) {

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








