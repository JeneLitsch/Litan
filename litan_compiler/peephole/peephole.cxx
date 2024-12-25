#include "peephole.hxx"
#include "../compile/InstructionBuffer.hxx"
#include <iostream>
#include <functional>
#include <optional>
#include "litan_core/type_code.hxx"

namespace ltn::c {
	namespace {
		using Search = std::function<std::uint64_t(std::span<const inst::Inst>)>;



		struct Pattern {
			Search search;
			std::vector<inst::Inst> replace;
		};



		Search wrap_search(const Search & search) {
			return search;
		}


		Search wrap_search(const inst::Inst & inst) {
			return [inst](std::span<const inst::Inst> span) -> std::uint64_t {
				if(span.empty()) {
					return 0;
				}
				if(inst == span.front()) {
					return 1;
				}
				else {
					return 0;
				}
			};
		}



		Search sequeunce(auto ... instructions) {
			std::array sub_searches { (wrap_search(instructions))...};
			return [sub_searches](std::span<const inst::Inst> span) -> std::uint64_t {
				if(span.size() < sub_searches.size()) {
					return 0;
				}
				else {
					std::uint64_t stride = 0;
					for (std::size_t i = 0; i < sub_searches.size(); i++) {
						if(std::uint64_t step = sub_searches[i](span)) {
							span = span.subspan(step);
							stride += step;
						}
						else{
							return 0;
						}
					}
					return stride;
				}
			};
		}



		Search search(inst::Inst instruction) {
			return wrap_search(instruction);
		}



		Search repeated(Search sub_search, std::uint64_t iterations) {
			return [sub_search, iterations](std::span<const inst::Inst> span) -> std::uint64_t {
				std::uint64_t stride = 0;
				for(std::uint64_t i = 0; i < iterations; i++) {
					if(auto step = sub_search(span)) {
						span = span.subspan(step);
						stride += step;
					}
					else {
						return 0;
					}
				}
				return stride;
			};
		}


		const Search null_and_return = sequeunce(inst::null(), inst::retvrn());



		const auto patterns = std::array {
			Pattern {
				.search = search(inst::load_x(0)),
				.replace = { inst::load_0() },
			},
			
			Pattern{
				.search = search(inst::load_x(1)),
				.replace = { inst::load_1() },
			},

			Pattern{
				.search = search(inst::load_x(2)),
				.replace = { inst::load_2() },
			},

			Pattern{
				.search = search(inst::load_x(3)),
				.replace = { inst::load_3() },
			},

			Pattern{
				.search = search(inst::store_x(0)),
				.replace = { inst::store_0() },
			},

			Pattern{
				.search = search(inst::store_x(1)),
				.replace = { inst::store_1() },
			},

			Pattern{
				.search = search(inst::store_x(2)),
				.replace = { inst::store_2() },
			},

			Pattern{
				.search = search(inst::store_x(3)),
				.replace = { inst::store_3() },
			},

			Pattern{
				.search = sequeunce(inst::newi(1), inst::add()),
				.replace = { inst::inc() },
			},

			Pattern{
				.search = sequeunce(inst::newi(1), inst::sub()),
				.replace = { inst::dec() },
			},

			Pattern{
				.search = repeated(null_and_return, 2),
				.replace = { inst::return_null() },
			},
			
			Pattern{
				.search = sequeunce(inst::retvrn(), null_and_return),
				.replace = { inst::retvrn() },
			},

			Pattern{
				.search = null_and_return,
				.replace = { inst::return_null() },
			},
		};



		InstructionBuffer apply_pattern(std::span<const inst::Inst> & span) {
			for(const auto & pattern : patterns) {
				if(auto steps = pattern.search(span)) {
					span = span.subspan(steps);
					return pattern.replace;
				}
			}

			InstructionBuffer buf;
			buf << span.front();
			span = span.subspan(1);
			return buf;
		}

		InstructionBuffer transform(std::span<const inst::Inst> input) {
			InstructionBuffer output;
			while (!input.empty()) {
				output << apply_pattern(input);
			}
			return output;
		}
	}



	std::vector<inst::Inst> peephole(const std::vector<inst::Inst> & input) {
		return transform(input).get();
	}
}