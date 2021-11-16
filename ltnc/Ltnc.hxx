#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include "Config.hxx"
#include "compile/Scope.hxx"
#include "compile/FxTable.hxx"
namespace ltn::c {
	class Ltnc {
	public:
		Ltnc() = default;
		virtual ~Ltnc() = default;
		void compile(std::istream & in, const std::string & sourceName);
		void yield(std::ostream & out);
	private:
		Config config;
		compile::Scope scope;
		compile::FxTable fxTable;
		std::stringstream buffer;
	};
}