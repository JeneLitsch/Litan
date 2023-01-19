#pragma once
#include "Language.hxx"

namespace ltn::c::lang {
	class Cpp : public Language {
	public:
		virtual std::string fx_start(const sst::Functional & fx) const override;
		virtual std::string fx_end(const sst::Functional & fx) const override;
		virtual std::string type_name(const type::Type & type) const override;

	};
}