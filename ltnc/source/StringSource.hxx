#pragma once
#include "Source.hxx"

namespace ltn::c {
	class StringSource : public Source {
	public:
		StringSource(const std::string & code, const std::string & name);
		virtual std::unique_ptr<std::istream> make_istream() const override;
		virtual std::string get_name() const override;
		virtual std::string get_full_name() const override;
	private:
		std::string code;
		std::string name;
	};
}