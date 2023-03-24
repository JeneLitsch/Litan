#include "Litan.hxx"
#include <vector>
#include <string>

namespace ltn {
	std::vector<std::uint8_t> build(const std::vector<ltn::c::Source> & user_sources) {
		ltn::c::Reporter reporter;
		auto sources = ltn::c::read_sources(std::vector<std::string>{}, reporter);
		for(auto & s : user_sources) {
			sources.push_back(s);
		}
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