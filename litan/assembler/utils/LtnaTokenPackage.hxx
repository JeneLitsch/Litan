#pragma once
#include <string>
#include <vector>

namespace ltn::a {
	struct TokenPackage{
		TokenPackage(){};

		TokenPackage(
			const std::string & line,
			const std::string & inst,
			const std::vector<std::string> & args,
			std::uint64_t lineNr)
		: 	line(line),
			inst(inst),
			args(args),
			lineNr(lineNr) {}
			
		TokenPackage(
			const std::string & line,
			const std::string & inst,
			const std::vector<std::string> & args)
		: 	line(line),
			inst(inst),
			args(args),
			lineNr(0) {}

		std::string line;
		std::string inst;
		std::vector<std::string> args;
		std::uint64_t lineNr;
	};
}