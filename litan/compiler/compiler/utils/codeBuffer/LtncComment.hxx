#pragma once
#include <string>
#include "LtncBufferObject.hxx"
namespace ltnc {
	class Comment : public IBufferObject {
	public:
		Comment(const std::string & string);
		virtual std::string toString() const override;
	private:
		std::string string;
	};
}