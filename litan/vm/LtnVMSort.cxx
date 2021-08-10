#include "LtnVM.hxx"
#include <bitset>
#include <iostream>
void ltn::VM::sortRadix() {

	const std::uint64_t ptr = this->env.acc.popU();
	HeapArray & arr = this->env.heap.access<HeapArray>(ptr);

	std::bitset<8> flags = this->getArg8();
	const bool useSign = flags.test(0);
	const bool order = flags.test(1);

	std::cout << useSign << order << std::endl;

	for(std::uint64_t val : arr) {
		std::cout << std::int64_t(val) << " : " << "0b" << std::bitset<64>(val) << std::endl;
	}

	std::array<std::vector<std::uint64_t>, 2> bucket;
	for(std::size_t i = 0; i < 64; i ++){
		for(std::uint64_t val : arr) {
			const bool bit = (val >> i) & 1;
			const bool flip = useSign && (i == 63);
			const bool bck = (bit == order) == flip;
			bucket[bck].push_back(val); 
		}
		std::copy(bucket[0].begin(), bucket[0].end(), arr.begin());
		std::copy(bucket[1].begin(), bucket[1].end(), arr.begin() + bucket[0].size());

		bucket[0].clear();
		bucket[1].clear();
	}
}
