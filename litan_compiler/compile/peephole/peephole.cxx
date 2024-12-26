#include "peephole.hxx"
#include "litan_compiler/compile/InstructionBuffer.hxx"
#include <iostream>
#include <functional>
#include <optional>
#include "litan_core/type_code.hxx"

namespace ltn::c {
	namespace {
		using Search = std::function<std::uint64_t(std::span<const inst::Inst>)>;
		using Replace = std::function<std::vector<inst::Inst>(std::span<const inst::Inst>)>;



		struct Pattern {
			Search search;
			Replace replace;
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




		Replace replace(inst::Inst instruction) {
			return [instruction] (std::span<const inst::Inst> match) -> std::vector<inst::Inst> {
				return { instruction };
			};
		}



		std::vector<inst::Inst> replace_with_tail (std::span<const inst::Inst> match) {
			if(match.empty()) {
				throw std::runtime_error { "replace_with_tail needs a match with at least one instruction." };
			}
			const inst::InstCall * call = std::get_if<inst::InstCall>(&match[0]);
			if(!call) {
				throw std::runtime_error { "replace_with_tail needs a call instruction at match[0]." };
			}
			return { inst::tail(call->label) };
		}	



		std::uint64_t is_call(std::span<const inst::Inst> span) {
			if(span.empty()) {
				return 0;
			} 
			const inst::InstCall * call = std::get_if<inst::InstCall>(&span.front());
			if(!call) {
				return 0;
			}
			if(call->opcode == OpCode::CALL) {
				return 1;
			}
			return 0;
		}



		const Search null_and_return = sequeunce(inst::null(), inst::retvrn());



		const auto patterns = std::array {
			Pattern {
				.search = search(inst::load_x(0)),
				.replace = replace(inst::load_0()),
			},
			
			Pattern{
				.search = search(inst::load_x(1)),
				.replace = replace(inst::load_1()),
			},

			Pattern{
				.search = search(inst::load_x(2)),
				.replace = replace(inst::load_2()),
			},

			Pattern{
				.search = search(inst::load_x(3)),
				.replace = replace(inst::load_3()),
			},

			Pattern{
				.search = search(inst::store_x(0)),
				.replace = replace(inst::store_0()),
			},

			Pattern{
				.search = search(inst::store_x(1)),
				.replace = replace(inst::store_1()),
			},

			Pattern{
				.search = search(inst::store_x(2)),
				.replace = replace(inst::store_2()),
			},

			Pattern{
				.search = search(inst::store_x(3)),
				.replace = replace(inst::store_3()),
			},

			Pattern{
				.search = sequeunce(inst::newi(1), inst::add()),
				.replace = replace(inst::inc()),
			},

			Pattern{
				.search = sequeunce(inst::newi(1), inst::sub()),
				.replace = replace(inst::dec()),
			},

			Pattern{
				.search = repeated(null_and_return, 2),
				.replace = replace(inst::return_null()),
			},
			
			Pattern{
				.search = sequeunce(inst::retvrn(), null_and_return),
				.replace = replace(inst::retvrn()),
			},

			Pattern{
				.search = null_and_return,
				.replace = replace(inst::return_null()),
			},

			Pattern {
				.search = sequeunce(is_call, inst::retvrn()),
				.replace = replace_with_tail,
			},
		};



		InstructionBuffer apply_pattern(std::span<const inst::Inst> & span) {
			for(const auto & pattern : patterns) {
				if(auto steps = pattern.search(span)) {
					std::span<const inst::Inst> match = span.subspan(0, steps);
					span = span.subspan(steps);
					return pattern.replace(match);
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