#pragma once
#include <string>
#include <sstream>

#include "LtncCodeObject.hxx"
#include "LtncAssemblyCode.hxx"
#include "LtncComment.hxx"
#include "LtncInst.hxx"
namespace ltn::c {
	class CodeBuffer {
	public:
		CodeBuffer(bool comments);
		CodeBuffer(const CodeBuffer & buffer);
		CodeBuffer & operator<<(const ICodeObject & instcode);
		CodeBuffer & operator<<(const std::string & code);
		CodeBuffer & operator<<(const char * code);
		CodeBuffer & operator<<(const Comment & comment);
		CodeBuffer & operator<<(const CodeBuffer & buffer);

		std::string str() const;	
	private:
		std::stringstream buffer;
		bool comments;
	};
}