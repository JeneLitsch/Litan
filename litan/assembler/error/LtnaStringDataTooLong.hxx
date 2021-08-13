#pragma once
#include "LtnaAssemblerError.hxx"
namespace ltn::a {
	class StringDataTooLong : public AssemblerError {
	public:
		StringDataTooLong();
	};
}