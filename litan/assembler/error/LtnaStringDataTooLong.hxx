#pragma once
#include "LtnaAssemblerError.hxx"
namespace ltna {
	class StringDataTooLong : public AssemblerError {
	public:
		StringDataTooLong();
	};
}