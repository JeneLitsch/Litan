#pragma once
#include "CompilerError.hxx"
#include "Reporter.hxx"
#include "Source.hxx"
#include "ltnc/inst/instructions.hxx"
#include "optimize/optimize.hxx"
#include "print/print.hxx"
#include "peephole/peephole.hxx"
#include "ltnc/tokens/Token.hxx"
#include "ltnc/lex/lexing.hxx"
#include <set>
#include "AddressTable.hxx"

namespace ltn::c {
	struct Instructions {
		std::vector<ltn::inst::Instruction> insts;
		std::set<std::string> init_functions;
		AddressTable global_table;
	};

	Tokens tokenize(
		std::vector<Source> sources,
		Reporter & reporter);

	ast::Program parse(
		Tokens & tokens,
		Reporter & reporter);

	Instructions compile(
		const ast::Program & program,
		Reporter & reporter);

	std::vector<std::uint8_t> assemble(
		const Instructions& instructions);
}