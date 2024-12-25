#pragma once
#include <functional>
#include "litan_compiler/sst/SST.hxx"

namespace ltn::c {
	class CustomLiteral {
	public:
		CustomLiteral(const std::string & type, auto fx)
			: type{type}
			, fx{wrap(fx)} {}

		sst::expr_ptr operator()(const std::string & value) const;
		const std::string & get_type() const;
	private:
		static sst::expr_ptr make(std::int64_t value);
		static sst::expr_ptr make(double value);
		static sst::expr_ptr make(const std::string & str);
		
		static sst::expr_ptr make(std::floating_point auto value) {
			make(static_cast<double>(value));
		}
		
		static sst::expr_ptr make(std::integral auto value) {
			make(static_cast<std::int64_t>(value));
		}
		
		std::function<sst::expr_ptr(const std::string &)> wrap(auto fx) {
			return [fx] (auto & value) { return make(fx(value)); };
		}

		std::string type;
		std::function<sst::expr_ptr(const std::string &)> fx;
	};
}