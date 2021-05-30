#pragma once 
#include <memory>
#include "LtncCompilerPack.hxx"
namespace ltnc {
	template<class OUT, class IN>
	class CompilerComponent {
	public:
		virtual OUT compile(CompilerPack & compPkg, const std::shared_ptr<IN> & node) const = 0;
	};
}