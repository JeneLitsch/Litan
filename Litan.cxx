#include "Litan.hxx"
#include <vector>
#include <string>

namespace ltn {
	std::vector<std::uint8_t> build(
		const std::vector<ltn::c::Source> & user_sources,
		const std::vector<ltn::c::CustomLiteral> & literals) {

		auto sources = user_sources;
		ltn::c::inject_stdlib(sources);
		auto tokens = ltn::c::lex(sources);
		auto ast = ltn::c::parse(tokens);
		auto sst = ltn::c::analyze(ast, literals);
		ltn::c::optimize(sst);
		auto [insts, link_info] = ltn::c::compile(sst);
		insts = ltn::c::peephole(insts);
		auto code = ltn::c::assemble(insts, link_info);
		return code;
	}
}