#include "shared.hxx"

ltn::c::sst::Program analysis_phase(std::string_view script_path) {
	auto sources = ltn::c::read_sources({script_path});
	auto ast = ltn::c::parse(sources);
	auto sst = ltn::c::analyze(ast);
	ltn::c::optimize(sst);
	return sst;
}



std::vector<ltn::c::inst::Inst> synthesis_phase(const ltn::c::sst::Program & sst) {
	return ltn::c::peephole(ltn::c::compile(sst));
}
