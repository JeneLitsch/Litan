#include "peephole.hxx"
#include "../compile/InstructionBuffer.hxx"
#include <iostream>
#include <functional>
#include <optional>
#include "ltn/type_code.hxx"

namespace ltn::c {
	namespace {
		using InstSpan = std::span<const inst::Inst>;
		using Step = std::function<bool(InstSpan)>;

		struct Pattern {
			std::vector<Step> steps;
			InstructionBuffer output;

			std::optional<InstructionBuffer> operator()(InstSpan span) const {
				for(std::size_t i = 0; i < steps.size(); ++i) {
					auto & step = steps[i];
					if(!step(span.subspan(i))) return std::nullopt;
				}
				InstructionBuffer buf;
				for(const auto & o : output.get()) {
					buf << o;
				}
				return buf;
			}

			Pattern & search() {
				return *this;
			}

			Pattern & search(const auto & first, const auto & ...args) {
				this->steps.push_back([first] (InstSpan span) -> bool {
					if(span.empty()) return false;
					return span.front() == first;
				});
				return search(args...);
			}

			Pattern & replace(const auto & ...args)  {
				(void)(this->output << ... << args); 
				return *this;
			}
		};



		const auto patterns = std::array {
			Pattern{}
				.search(inst::load_x(0))
				.replace(inst::load_0()),

			Pattern{}
				.search(inst::load_x(1))
				.replace(inst::load_1()),

			Pattern{}
				.search(inst::load_x(2))
				.replace(inst::load_2()),

			Pattern{}
				.search(inst::load_x(3))
				.replace(inst::load_3()),


			Pattern{}
				.search(inst::store_x(0))
				.replace(inst::store_0()),

			Pattern{}
				.search(inst::store_x(1))
				.replace(inst::store_1()),

			Pattern{}
				.search(inst::store_x(2))
				.replace(inst::store_2()),

			Pattern{}
				.search(inst::store_x(3))
				.replace(inst::store_3()),

			Pattern{}
				.search(inst::newi(1), inst::add())
				.replace(inst::inc()),

			Pattern{}
				.search(inst::newi(1), inst::sub())
				.replace(inst::dec()),

			Pattern{}
				.search(inst::retvrn(), inst::null(), inst::retvrn())
				.replace(inst::retvrn()),
		};



		InstructionBuffer transform(std::span<const inst::Inst> & span) {
			for(const auto & pattern : patterns) {
				if(auto x = pattern(span)) {
					span = span.subspan(pattern.steps.size());
					return *x;
				}
			}

			InstructionBuffer buf;
			buf << span.front();
			span = span.subspan(1);
			return buf;
		}
	}



	std::vector<inst::Inst> peephole(const std::vector<inst::Inst> & input) {
		InstructionBuffer final_buf;
		std::span<const inst::Inst> span = input;
		while (!span.empty()) {
			final_buf << transform(span);
		}
		return final_buf.get();
	}
}