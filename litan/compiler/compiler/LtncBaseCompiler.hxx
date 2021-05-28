#pragma once
#include <string>
namespace ltnc {
	class BaseCompiler {
	public:
		
		void activateComments(bool active);
		void setOptimization(unsigned active);
	protected:
		unsigned getOptimizationLevel() const;
		std::string pushToStack(const unsigned amount) const;
		std::string popFromStack(const unsigned amount) const;
		std::string comment(const std::string & content) const;
	private:
		bool addComments = false;
		unsigned optimizations = 0;
	};
}