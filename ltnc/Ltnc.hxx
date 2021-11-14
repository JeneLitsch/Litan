#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include "SymbolTable.hxx"
#include "Config.hxx"
namespace ltn::c {
	class Ltnc {
	public:
		Ltnc() = default;
		virtual ~Ltnc() = default;
		void compile(std::istream & in, const std::string & sourceName);
		void yield(std::ostream & out);
	private:
		Config config;
		SymbolTable sTable;
		std::stringstream buffer;
	};
}