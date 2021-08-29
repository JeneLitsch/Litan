#include "LtncCtorGenerator.hxx"
#include "Unused.hxx"

std::string registerCtor(
	ltn::c::SymbolTable & symbolTable,
	const ltn::c::Type & type, bool useParamters) {

	// add members as ctor parameter
	// skip for default ctor
	std::vector<ltn::c::Param> params;
	if(useParamters) {
		for(const auto & member : type.members) {
			params.push_back(ltn::c::Param(member->typeId, ltn::c::VarId(member->name)));
		}
	}
	
	ltn::c::DebugInfo automatic(0,0, "", "");

	// register function and create jumpMark 
	ltn::c::FunctionSignature signature(type.id, type.id.name, params, type.id.ns);
	symbolTable.insert(automatic, signature);
	return symbolTable.match(automatic, signature).jumpMark;
}



ltn::c::CodeBuffer allocateStruct(std::size_t size) {
	ltn::c::CodeBuffer code(false);
	code << ltn::c::Inst::allocateStruct(size);
	return code;
}



ltn::c::CodeBuffer readParameters(std::size_t size) {
	ltn::c::CodeBuffer code(false);
	code << ltn::c::Inst::stackalloc(static_cast<std::uint32_t>(size));
	// read params from acc
	for(unsigned i = 0; i < size; i++) {
		code << ltn::c::Inst::store(i);
	}
	return code;
}



ltn::c::CodeBuffer initMembers(std::size_t size) {
	// write to object on heap
	ltn::c::CodeBuffer code(false);
	for(unsigned i = 0; i < size; i++) {
		code << ltn::c::AssemblyCode("copy");
		code << ltn::c::Inst::load(static_cast<std::uint32_t>(size - i - 1));
		code << ltn::c::Inst::structWrite(i);
	}
	return code;
}



ltn::c::CodeBuffer ltn::c::CtorGenerator::defaultCtor(
	CompilerPack & compilePkg,
	const Type & type) const {

	std::string jumpMark = registerCtor(compilePkg.getSymbolTable(), type, false);

	CodeBuffer code = compilePkg.codeBuffer();
	code << Comment(type.id.name);
	code << AssemblyCode("-> " + jumpMark);
	code << allocateStruct(type.members.size());
	code << AssemblyCode("return");
	code << AssemblyCode("\n");
	return code;
}



ltn::c::CodeBuffer ltn::c::CtorGenerator::parameterCtor(
	CompilerPack & compilePkg,
	const Type & type) const {

	std::string jumpMark = registerCtor(compilePkg.getSymbolTable(), type, true);

	const std::size_t size = type.members.size();
	// ctor head 
	CodeBuffer code = compilePkg.codeBuffer();
	code << Comment(type.id.name);
	code << AssemblyCode("-> " + jumpMark);
	code << readParameters(size);
	code << allocateStruct(size);
	code << initMembers(size);
	code << AssemblyCode("return");
	code << AssemblyCode("\n");
	return code;
}