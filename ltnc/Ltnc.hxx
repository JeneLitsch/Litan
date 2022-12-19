#pragma once
#include "CompilerError.hxx"
#include "Reporter.hxx"
#include "source/Source.hxx"
#include "source/FileSource.hxx"
#include "source/StringSource.hxx"
#include "ltnc/inst/inst.hxx"
#include "optimize/optimize.hxx"
#include "print/print.hxx"
#include "peephole/peephole.hxx"
#include "ltnc/tokens/Token.hxx"
#include "ltnc/lex/lexing.hxx"
#include <set>
#include "AddressTable.hxx"
#include "ltnc/ast/AST.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	struct Instructions {
		std::vector<inst::Inst> insts;
		std::set<std::string> init_functions;
		AddressTable global_table;
	};

	Tokens tokenize(
		std::vector<std::unique_ptr<Source>> sources,
		Reporter & reporter);

	ast::Source parse(
		Tokens & tokens,
		Reporter & reporter);

	sst::Program analyze(
		const ast::Source & source,
		Reporter & reporter);

	Instructions compile(
		const sst::Program & program,
		Reporter & reporter);

	std::vector<std::uint8_t> assemble(
		const Instructions& instructions);
}