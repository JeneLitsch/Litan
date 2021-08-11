#pragma once
#include <vector>
#include "LtnError.hxx"
namespace ltn {
	class CumulatedError : public Error {
		friend std::ostream & operator<<(
			std::ostream & stream,
			const CumulatedError & error);
	public:
		CumulatedError();
		void pushError(const Error & error);
		virtual std::string str() const override;
		bool throwable() const;
	private:
		std::vector<Error> suberrors;
	};
}