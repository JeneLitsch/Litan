#pragma once
#include "Api.hxx"
namespace ltn::vm::ext {
	class External {
	public:
		External(std::size_t parameters);
		virtual void operator()(Api & api) = 0;
		std::size_t getParameters() const;
	private:
		std::size_t parameters;
	};
}