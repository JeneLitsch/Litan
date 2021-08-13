#pragma once
#include <string>
#include <vector>
#include "LtncCodeObject.hxx"
namespace ltn::c {
	class AssemblyCode : public ICodeObject {
	public:
		AssemblyCode(const std::string & string);
		AssemblyCode(const std::vector<std::string> & strings);
		virtual std::string toString() const override;
	private:
		std::string string;
	};
}