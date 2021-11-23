#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include "Config.hxx"
#include "Backend.hxx"
namespace ltn::c {
	class Ltnc {
	public:
		Ltnc(std::unique_ptr<Backend> backend) : backend(std::move(backend)) {}
		virtual ~Ltnc() = default;
		void compile(std::istream & in, const std::string & sourceName);
		void yield(std::ostream & out);
	private:
		Config config;
		std::size_t line = 1;
		std::unique_ptr<Backend> backend;
	};
}