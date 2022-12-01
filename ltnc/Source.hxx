#pragma once
#include <string>
#include <istream>
#include <fstream>
#include "stdxx/memory.hxx"

namespace ltn::c {
	class Source {
	public:
		Source(const std::string & source_name, std::unique_ptr<std::istream> in) :
			in { std::move(in) },
			source_name { source_name } {}

		template<typename InStream>
		static Source make(const std::string & name, auto ... args) {
			return Source { name, stx::make_unique<InStream>(args...) };
		}

		const std::string & name() const {
			return this->source_name;
		}

		std::istream & stream() {
			return *in;
		}

		operator bool() const {
			return static_cast<bool>(*this->in);
		}
	private:
		std::unique_ptr<std::istream> in;
		std::string source_name;
	};
}