#include "peephole.hxx"
#include "../compile/utils/InstructionBuffer.hxx"
#include <iostream>
#include <functional>
#include "ltn/type_code.hxx"

namespace ltn::c {
	namespace {
		using InstSpan = std::span<const ltn::inst::Instruction>;
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
					using T = std::decay_t<decltype(first)>;
					if(span.empty()) return false;
					const T * t = span.front().as<T>();
					return t && t->args == first.args;
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
				.search(inst::Readx{0})
				.replace(inst::Read0{}),

			Pattern{}
				.search(inst::Readx{1})
				.replace(inst::Read1{}),

			Pattern{}
				.search(inst::Readx{2})
				.replace(inst::Read2{}),

			Pattern{}
				.search(inst::Readx{3})
				.replace(inst::Read3{}),


			Pattern{}
				.search(inst::Writex{0})
				.replace(inst::Write0{}),

			Pattern{}
				.search(inst::Writex{1})
				.replace(inst::Write1{}),

			Pattern{}
				.search(inst::Writex{2})
				.replace(inst::Write2{}),

			Pattern{}
				.search(inst::Writex{3})
				.replace(inst::Write3{}),

			Pattern{}
				.search(inst::Newi{1}, inst::Add{})
				.replace(inst::Inc{}),

			Pattern{}
				.search(inst::Newi{1}, inst::Sub{})
				.replace(inst::Dec{}),

			Pattern{}
				.search(inst::Cast{std::vector<std::uint8_t>{'b'}})
				.replace(inst::CastBool{}),

			Pattern{}
				.search(inst::Cast{std::vector<std::uint8_t>{'c'}})
				.replace(inst::CastChar{}),

			Pattern{}
				.search(inst::Cast{std::vector<std::uint8_t>{'i'}})
				.replace(inst::CastInt{}),

			Pattern{}
				.search(inst::Cast{std::vector<std::uint8_t>{'f'}})
				.replace(inst::CastFloat{}),

			Pattern{}
				.search(inst::Return{}, inst::Null{}, inst::Return{})
				.replace(inst::Return{}),
		};

		InstructionBuffer transform(std::span<const ltn::inst::Instruction> & span) {
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

	std::vector<ltn::inst::Instruction> peephole(
		const std::vector<ltn::inst::Instruction> & input) {
		InstructionBuffer final_buf;
		std::span<const ltn::inst::Instruction> span = input;
		while (!span.empty()) {
			final_buf << transform(span);
		}
		return final_buf.get();
	}
}