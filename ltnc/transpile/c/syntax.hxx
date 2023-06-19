#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <memory>
#include "Node.hxx"

namespace ltn::c::trans::c {
	struct Variable {
		std::string type;
		std::string name;
		std::string value;
	};

	struct Member {
		std::string type;
		std::string name;
	};

	struct Struct {
		std::string name;
		std::vector<Member> members;
	};

	struct Function {
		std::string name;
		std::uint64_t arity;
		Node body;
	};

	struct Line {
		std::string code;
	};

	struct Block {
		std::vector<Node> elements;
	};

	struct Include {
		std::string header;
	};

	struct Bundle {
		std::vector<Node> elements;
	};

	void print_c(std::ostream &, const Variable &, std::uint64_t indent);
	void print_c(std::ostream &, const Member &, std::uint64_t indent);
	void print_c(std::ostream &, const Struct &, std::uint64_t indent);
	void print_c(std::ostream &, const Function &, std::uint64_t indent);
	void print_c(std::ostream &, const Block &, std::uint64_t indent);
	void print_c(std::ostream &, const Line &, std::uint64_t indent);
	void print_c(std::ostream &, const Include &, std::uint64_t indent);
	void print_c(std::ostream &, const Bundle &, std::uint64_t indent);
}