#include "LtncCompilerFunctions.hxx"

namespace ltn::c {
	class LiteralExtractor {
	public:
		LiteralExtractor(CompilerPack & compPkg)
			: compPkg(compPkg) {}
		
		ExprInfo operator()(std::int64_t value) {
			CodeBuffer code = compPkg.codeBuffer();
			code << Inst::newi(value);
			return ExprInfo(TypeId(TInt), code, ConstValue(value));
		}

		ExprInfo operator()(double value) {
			CodeBuffer code = compPkg.codeBuffer();
			code << Inst::newf(value);
			return ExprInfo(TypeId(TFloat), code, ConstValue(value));
		}

		ExprInfo operator()(const std::string & value) {
			CodeBuffer code = compPkg.codeBuffer();
			code << AssemblyCode("heap::allocate::string");
			code << Inst::stringData(value);
			return ExprInfo(TypeId(TString), code);
		}

		ExprInfo operator()(bool value) {
			CodeBuffer code(false);
			code << Inst::newl(value);
			return ExprInfo(TypeId(TBool), code);
		}

		ExprInfo operator()([[maybe_unused]] std::monostate value) {
			CodeBuffer code(false);
			code << Inst::newl(0);
			return ExprInfo(TypeId(TPointer), code);
		}

	private:
		CompilerPack & compPkg;
	};
}

ltn::c::ExprInfo ltn::c::compile::literal(CompilerPack & compPkg, const ExprLiteral & expr) {
	return std::visit(LiteralExtractor(compPkg), expr.value);
}