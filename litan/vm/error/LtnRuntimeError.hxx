#pragma once
#include "LtnError.hxx"
namespace ltn::vm {
	class RuntimeError : public Error {
	public:
		RuntimeError();
		RuntimeError(const std::string & msg);
	};
}