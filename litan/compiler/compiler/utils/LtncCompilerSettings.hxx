#pragma once

namespace ltnc {
	class CompilerSettings {
	public:
		CompilerSettings(bool comments, unsigned optimization);
		bool areCommentsActive() const;
		unsigned getOptimizationLevel() const;
	private:
		bool addComments = false;
		unsigned optimizations = 0;
	};
}