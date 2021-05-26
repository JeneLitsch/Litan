#pragma once
#include <string>
#include <vector>

namespace ltn{
	struct TokenPackage{
		TokenPackage(){};
		TokenPackage(const std::string & line, const std::string & inst, const std::vector<std::string> & args)
		: line(line), inst(inst), args(args) {}
		std::string line;
		std::string inst;
		std::vector<std::string> args;
	};
}