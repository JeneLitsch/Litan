#include "Litan.hxx"
#include <vector>
#include <string>

namespace ltn {
	std::vector<std::uint8_t> build(
		const std::vector<ltn::c::Source> & user_sources,
		const std::vector<ltn::c::CustomLiteral> & literals) {

		ltn::c::Reporter reporter;
		auto sources = user_sources;
		ltn::c::inject_stdlib(sources);
		auto tokens = ltn::c::lex(sources, reporter);
		auto ast = ltn::c::parse(tokens, reporter);
		auto sst = ltn::c::analyze(ast, reporter);
		ltn::c::optimize(sst);
		auto [insts, link_info] = ltn::c::compile(sst, reporter);
		insts = ltn::c::peephole(insts);
		auto code = ltn::c::assemble(insts, link_info);
		reporter.may_throw();
		return code;
	}
}