#pragma once
#include "LtnError.hxx"
namespace ltn {
	class RuntimeError : public Error {
	public:
		RuntimeError();
		RuntimeError(const std::string & msg);
	};
}