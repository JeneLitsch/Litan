#pragma once
#include "LtnRuntimeError.hxx"
namespace ltn::vm {
	class AccessViolation : public RuntimeError {
	public:
		std::uint64_t getPtr() const;
		std::uint64_t getIdx() const;
		const std::string & getType();
	protected:
		AccessViolation(
			const std::string & msg,
			std::uint64_t ptr,
			std::uint64_t idx,
			const std::string & type);
	private:
		std::uint64_t ptr;
		std::uint64_t idx;
		std::string type;
	};
}
