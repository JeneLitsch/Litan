#pragma once
#include <string>
#include "ltnc/sst/SST.hxx"

namespace ltn::c::lang {
	class Language {
	public:
		Language() = default;
		virtual ~Language() = default;

		virtual std::string fx_begin(const sst::Functional & fx) const = 0;
		virtual std::string fx_end(const sst::Functional & fx) const = 0;

		virtual std::string block_begin() const = 0;
		virtual std::string block_end() const = 0;

		virtual std::string type_name(const type::Type & type) const = 0;

		std::string indent(unsigned indentation) const;
	};
}