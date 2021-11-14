#pragma once
#include <istream>
#include <ostream>
namespace ltnc {
	class Ltnc {
	public:
		Ltnc() = default;
		virtual ~Ltnc() = default;
		void compile(std::istream & in, const std::string & sourceName);
		void yield(std::ostream & out);
	};
}