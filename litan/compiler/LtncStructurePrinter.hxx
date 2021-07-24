#pragma once
#include "LtncAst.hxx"
#include <ostream>

namespace ltnc {
	class StructurePrinter {
	public:
		StructurePrinter(const Program & program);
		std::string print() const;
	private:
		const Program & program; 
	};

	std::ostream & operator<<(std::ostream & stream, const StructurePrinter & printer);
}