#pragma once
#include <string>
#include "LtncCodeBuffer.hxx"
namespace ltnc {
	struct StmtInfo {
		StmtInfo(const CodeBuffer & code, unsigned stackalloc)
			: code(code), stackalloc(stackalloc)  {}
		
		StmtInfo(const StmtInfo & info) 
			: code(info.code), stackalloc(info.stackalloc) {}
		
		const CodeBuffer code;
		const unsigned stackalloc;
	};
}