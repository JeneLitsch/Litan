#pragma once
#include "CompilerError.hxx"
#include "Reporter.hxx"
#include "Source.hxx"
#include "ltn/InstructionSet.hxx"
#include "optimize/optimize.hxx"
#include "print/print.hxx"
#include "peephole/peephole.hxx"
#include "ltnc/lex/Tokens.hxx"

namespace ltn::c {
	Tokens tokenize(
		std::vector<Source> sources,
		Reporter & reporter);

	ast::Program parse(
		Tokens & tokens,
		Reporter & reporter);

	std::vector<ltn::inst::Instruction> compile(
		const ast::Program & program,
		Reporter & reporter);

	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Instruction> & instructions);
}