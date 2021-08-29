#pragma once
#include "LtncAst.hxx"
#include <ostream>

namespace ltn::c {
	class StructurePrinter {
	public:
		StructurePrinter(const Program & program);
		std::string print() const;
	private:
		static std::string toString(const std::vector<std::string> & strs);
		const Program & program; 
	};

	std::ostream & operator<<(std::ostream & stream, const StructurePrinter & printer);
}