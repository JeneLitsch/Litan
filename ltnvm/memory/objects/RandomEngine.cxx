#include "RandomEngine.hxx"

namespace ltn::vm {
	struct Splitter {
		RandomEngine operator()(std::mt19937_64 & rng) {
			return RandomEngine{std::mt19937_64{rng()}};
		};
	};

	RandomEngine RandomEngine::split() {
		return std::visit(Splitter{}, this->engine);
	}
}