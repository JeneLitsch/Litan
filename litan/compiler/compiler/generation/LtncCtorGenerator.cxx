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

ltn::c::CodeBuffer ltn::c::CtorGenerator::defaultCtor(
	CompilerPack & compilePkg,
	const Type & type) const {

	std::string jumpMark = registerCtor(compilePkg.getSymbolTable(), type, false);

	CodeBuffer code = compilePkg.codeBuffer();
	code << Comment(type.id.name);
	code << AssemblyCode("-> " + jumpMark);
	code << AssemblyCode("heap::allocate::array");
	code << AssemblyCode("copy");
	code << Inst::newl(static_cast<std::uint32_t>(type.members.size()));
	code << AssemblyCode("array::resize");
	code << AssemblyCode("return");
	code << AssemblyCode("\n");
	return code;
}

ltn::c::CodeBuffer ltn::c::CtorGenerator::parameterCtor(
	CompilerPack & compilePkg,
	const Type & type) const {

	std::string jumpMark = registerCtor(compilePkg.getSymbolTable(), type, true);

	// ctor head 
	CodeBuffer code = compilePkg.codeBuffer();
	code << Comment(type.id.name);
	code << AssemblyCode("-> " + jumpMark);
	code << AssemblyCode("stackalloc " + std::to_string(type.members.size()));
	
	std::uint32_t index = 0; 
	// read params from acc
	for(const auto & member : type.members) {
		UNUSED(member);
		code << Inst::store(index);
		index++;
	}

	// allocate object
	code << AssemblyCode("heap::allocate::array");
	
	// write to object on heap
	for(const auto & member : type.members) {
		index--;
		UNUSED(member);
		code << AssemblyCode("copy");
		code << Inst::load(index);
		code << AssemblyCode("array::pushback");
	}

	code << AssemblyCode("return");
	code << AssemblyCode("\n");
	return code;
}