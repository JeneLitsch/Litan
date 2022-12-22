#include "Litan.hxx"

namespace ltn {
	std::vector<std::uint8_t> build(const std::vector<ltn::c::Source> & sources) {
		ltn::c::Reporter reporter;
		auto tokens = ltn::c::tokenize(sources, reporter);
		auto ast = ltn::c::parse(tokens, reporter);
		auto sst = ltn::c::analyze(ast, reporter);
		ltn::c::optimize(sst);
		auto insts = ltn::c::compile(sst, reporter);
		insts.insts = ltn::c::peephole(insts.insts);
		auto code = ltn::c::assemble(insts);
		reporter.may_throw();
		return code;
	}
}