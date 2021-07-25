#include "LtncConstructorGenerator.hxx"
#include "Unused.hxx"

ltnc::CodeBuffer ltnc::ConstructorGenerator::defaultCtor(
	CompilerPack & compilePkg,
	const Type & type) const {

	FunctionSignature signature(type.id, type.id.name, {}, type.id.ns);
	compilePkg.getSymbolTable().insert(signature);
	std::cout << "TEST" << std::endl;
	std::string jumpMark = compilePkg.getSymbolTable().match(signature).jumpMark;

	CodeBuffer code = compilePkg.codeBuffer();
	code << Comment(type.id.name);
	code << AssemblyCode("-> " + jumpMark);
	code << AssemblyCode("array::new");
	for(const auto & member : type.members) {
		UNUSED(member);
		code << AssemblyCode("copy");
		code << Inst::newl(0); // init with nullptr;
		code << AssemblyCode("array::pushb");
	}
	code << AssemblyCode("return");
	code << AssemblyCode("\n");
	return code;
}

ltnc::CodeBuffer ltnc::ConstructorGenerator::parameterCtor(
	CompilerPack & compilePkg,
	const Type & type) const {

	std::vector<Param> params;
	for(const auto & member : type.members) {
		params.push_back(Param(member->typeId, VarId(member->name)));
	}
	
	FunctionSignature signature(type.id, type.id.name, params, type.id.ns);
	compilePkg.getSymbolTable().insert(signature);
	std::cout << "TEST" << std::endl;
	std::string jumpMark = compilePkg.getSymbolTable().match(signature).jumpMark;

	CodeBuffer code = compilePkg.codeBuffer();
	std::uint32_t index = 0; 
	code << Comment(type.id.name);
	code << AssemblyCode("-> " + jumpMark);
	code << AssemblyCode("stackalloc " + std::to_string(type.members.size()));
	
	for(const auto & member : type.members) {
		UNUSED(member);
		code << Inst::store(index); // init with nullptr;
		index++;
	}

	code << AssemblyCode("array::new");
	for(const auto & member : type.members) {
		index--;
		UNUSED(member);
		code << AssemblyCode("copy");
		code << Inst::load(index); // init with nullptr;
		code << AssemblyCode("array::pushb");
	}

	code << AssemblyCode("return");
	code << AssemblyCode("\n");
	return code;
}