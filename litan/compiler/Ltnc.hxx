#pragma once
#include <string>
namespace ltnc {
	class LTNC {
	public:
		std::string compile(
			const std::string & source,
			bool comments,
			bool silent,
			unsigned optimizationLevel) const;
	private:
	};
}