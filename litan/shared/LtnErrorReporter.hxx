#pragma once
#include <vector>
#include "LtnError.hxx"

namespace ltn {
	class ErrorReporter : public Error {
		friend std::ostream & operator<<(
			std::ostream & stream,
			const ErrorReporter & error);
	public:
		ErrorReporter();
		ltn::ErrorReporter & operator<<(const Error & error);
		virtual std::string str() const override;
		bool throwable() const;
	private:
		std::vector<Error> suberrors;
	};
}