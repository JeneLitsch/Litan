#pragma once 
#include <memory>
#include "LtncCompilerPack.hxx"
namespace ltnc {
	template<class OUT, class IN>
	class CompilerComponent {
	public:
		virtual OUT compile(CompilerPack & compPkg, const std::shared_ptr<IN> & node) const = 0;
		std::string comment(const CompilerPack & compPkg, const std::string & content) const {
			if(compPkg.getSettings().areCommentsActive()) {
				return "// " + content + "\n";
			}
			else{
				return "";
			}
		}
	};
}