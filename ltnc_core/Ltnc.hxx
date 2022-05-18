#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include <span>
#include "Config.hxx"
#include "Backend.hxx"
#include "CompilerError.hxx"
#include "Reporter.hxx"
namespace ltn::c {
	class Ltnc {
	public:
		Ltnc(std::unique_ptr<Backend> backend);
		virtual ~Ltnc() = default;
		void compile(std::istream & in, const std::string & sourceName);
		void optimize();
		void yield(std::ostream & out);
	private:
		Config config;
		std::unique_ptr<Backend> backend;
		ast::Program program;
		Reporter reporter;
	};
}