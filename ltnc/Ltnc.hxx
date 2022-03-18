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
		Ltnc(std::unique_ptr<Backend> backend) : backend(std::move(backend)) {}
		virtual ~Ltnc() = default;
		const std::span<const std::string_view> stdlib() const;
		void compile(std::istream & in, const std::string & sourceName);
		void yield(std::ostream & out);
	private:
		Config config;
		std::unique_ptr<Backend> backend;
		ast::Program program;
		Reporter reporter;
	};
}